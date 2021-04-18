#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include <MessageLib/StartTransMessage.hpp>
#include <MessageLib/ResponseMessage.hpp>
#include <MessageLib/RequestMessage.hpp>
#include <MessageLib/EncryptedMessage.hpp>
#include <MessageLib/IMessage.hpp>

#include <SecurityLib/ConfigurationGenerator.hpp>
#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>

#include <Client/Client.hpp>

 Client::Client() {
    _key = "";
    _server_sign_key = "";
    _server_pub_key = "";

    _socket_fd = 0;
    _is_running.fetch_add(1, std::memory_order_seq_cst); // Show as running.

    // Spin up a security service.
    securitylib::ConfigurationGenerator config_generator;
    securitylib::SecurityConfiguration config = config_generator.GenerateDefaultConfiguration();

    _sec_service = std::make_shared<securitylib::SecurityService>(config);
 }

// Establish a connection to the server.
 void Client::StartClient(std::string name) {
    _name = name;
    struct sockaddr_in ipOfServer;

    if((_socket_fd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return;
    }
 
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(56000);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(_socket_fd, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return;
    }
 }


void Client::GetEncryptionKeys() {
    _threads.push_back(std::thread(&Client::GetEncryptionKeysWithQueue, this));
}


void Client::GetEncryptionKeysWithQueue() {
    // Lock mutex for the condvar...
    std::unique_lock lock(_get_keys_mutex);

    // Create a buffer
    unsigned char buffer[4096];
    memset(buffer, '0' ,sizeof(buffer));

    // Create the StartTrans message to ask for public signing key
    msglib::StartTransMessage tx(_name);
    tx.Pack(buffer);

    // Add message to the queue
    AddBufferToQueue(buffer, 4096);

    // Wait for the response...    
    _get_keys_cv.wait(lock, [this] {return (_server_sign_key != "" || _kill_threads.load() != 0) ? true : false; });
    if (_kill_threads.load() != 0) {
        return;
    }

    // Generate the encryption intermediate keys
    std::string private_key, public_key;
    _sec_service->keyExchangeService->GenerateIntermediateKeys(private_key, public_key);

    // Trade the keys.
    // Create the request.
    msglib::RequestMessage request_keys("TradeKeys " + public_key, _name);
    request_keys.Pack(buffer);

    // Add the request to the queue.
    AddBufferToQueue(buffer, 4096);

    // Wait for the response...
    _get_keys_cv.wait(lock, [this] {return (_server_pub_key != "" || _kill_threads.load() != 0) ? true : false; });
    if (_kill_threads.load() != 0) {
        return;
    }

    // Generate the final key. _key in the function argument is the server's public key
    // _key after it has been assigned is the full encryption key 
    _key = _sec_service->keyExchangeService->GenerateFinalKey(private_key, _server_pub_key);

    // Test message
    std::string plain_text = "Encryption Test.";
    std::string cipher_text = _sec_service->encryptionService->EncryptData(_key, _name, plain_text);

    msglib::EncryptedMessage msg(cipher_text, _name);
    msg.Pack(buffer);
    AddBufferToQueue(buffer, 4096);

    _can_encrypt.fetch_add(1, std::memory_order_seq_cst);
}

void Client::SendQueue() {
    while(_kill_threads.load() != 1) {
        // Wait a second
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Make storage container.
        std::string msg;

        // Check if there's something in the queue.
        {
            std::unique_lock lock(_messageQueueLock);
            if (_messageQueue.size() < 1) {
                continue;
            }

            msg = _messageQueue.front();
            _messageQueue.pop();
        }

        send(_socket_fd, msg.c_str(), msg.size(), 0);
    }
 }

 void Client::AddBufferToQueue(unsigned char* buffer, int length) {
    std::string packed_data((char*)buffer, length);
    {
        std::unique_lock lock(_messageQueueLock);
        _messageQueue.push(packed_data);
    }
 }

 void Client::Listen() {
    unsigned char buffer[4096];
    memset(buffer, '0', sizeof(buffer));

    while(_kill_threads.load() != 1) {
        // Wait a second
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Wait for recv
        recv(_socket_fd, buffer, 4096, MSG_DONTWAIT);

        // Call the handle function.
        HandleIncoming(buffer);

        // Flush Buffer
        memset(buffer, '0', sizeof(buffer));
    }
 }

 void Client::HandleIncoming(unsigned char* buffer) {
    // Get the message ID from the buffer.
    int messageId;
    msglib::IMessage::RetrieveInt(&messageId, buffer, 0);

    switch (messageId) {
        case 3: // Response message
            {
                msglib::ResponseMessage responseMessage;
                responseMessage.Unpack(buffer);

                // See what has been requested...
                if (responseMessage.requestSent == "StartTrans") {
                    // If start trans..

                    // Store key and notify thread
                    {
                        std::unique_lock lock(_get_keys_mutex);
                        _server_sign_key = responseMessage.response;

                        _get_keys_cv.notify_one();
                    }
                }
                else if (responseMessage.requestSent == "TradeKeys") {
                    // If trade keys...

                    // Store servers public key and notify thread
                    {
                        std::unique_lock lock(_get_keys_mutex);
                        _server_pub_key = responseMessage.response;

                        _get_keys_cv.notify_one();
                    }
                }
            }
            
            break;

        case 4: // Encrypted message
            {
                // Unpack buffer into a message
                msglib::EncryptedMessage enc_msg;
                enc_msg.Unpack(buffer);

                // Decrypt the message.
                std::string decrypted_message = _sec_service->encryptionService->DecryptData(_key, _name, enc_msg.message);

                // DEBUG, print out message.
                std::cout << "Message Decrypted: " << decrypted_message << std::endl;
            }
            break;

        default:
            break;
    }
 }

 void Client::StartCommunicationThreads() {
    // Check for threads in _threads
    if (_threads.size() != 0) {
        return;
    }

    // Set up the atomic flag to be 0.
    unsigned char atomic_current = _kill_threads.load();
    _kill_threads.fetch_sub(atomic_current, std::memory_order_seq_cst);

    // Create the threads.
    _threads.push_back(std::thread(&Client::SendQueue, this));
    _threads.push_back(std::thread(&Client::Listen, this));
 }

 void Client::KillCommunicationThreads() {
    // Check for threads in _threads.
    if (_threads.size() == 0) {
        return;
    }

    // Set the flag to let the threads finish.
    _kill_threads.fetch_add(1, std::memory_order_seq_cst);

    // If there's a get keys thread going, notify it...
    {
        std::unique_lock lock(_get_keys_mutex);
        _get_keys_cv.notify_all();
    }

    // Join the threads and remove them from the vector.
    int size = _threads.size();
    for(int i = 0; i < size; i++) {
        _threads.back().join();
        _threads.pop_back();
    }    
 }

void Client::StopAll() {
    KillCommunicationThreads();

    // Set up the atomic flag to be 0.
    unsigned char atomic_current = _is_running.load();
    _is_running.fetch_sub(atomic_current, std::memory_order_seq_cst);

    close(_socket_fd);
}

bool Client::IsRunning() {
    return _is_running.load() != 0;
}

void Client::SendStatusUpdatesThreadFunction() {
    unsigned char buffer[4096];
    memset((void*)buffer, '0', sizeof(buffer));

    // Check if we can encrypt.
    while (_can_encrypt.load() == 0) {
        if (_kill_threads.load() != 0) { // If it needs to be killed early.
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    int i = 1;
    // Send status updates
    while(_kill_threads.load() != 1) {

        // Create and pack a message.
        std::string message = "StatusUpd ";
        message = message.append("test=" + std::to_string(i));
        message = message.append(",param2=hello");
        std::string encrypted_string = _sec_service->encryptionService->EncryptData(_key, _name, message);

        std::string decrypted_message = _sec_service->encryptionService->DecryptData(_key, _name, encrypted_string);

        std::cout << "Pre-Decrypted Message: " << decrypted_message << std::endl;

        msglib::EncryptedMessage enc_msg(encrypted_string, _name);
        enc_msg.Pack(buffer);

        AddBufferToQueue(buffer, 4096);

        i++;

        // Wait for 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}

void Client::SendStatusUpdates() {
    _threads.push_back(std::thread(&Client::SendStatusUpdatesThreadFunction, this));
}