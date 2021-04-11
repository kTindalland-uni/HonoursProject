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

#include <Client/Client.hpp>

 Client::Client() {
    _name = "Client1";
    _socket_fd = 0;
    _is_running.fetch_add(1, std::memory_order_seq_cst); // Show as running.
 }

// Establish a connection to the server.
 void Client::StartClient() {
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
    unsigned char buffer[4096];
    memset(buffer, '0' ,sizeof(buffer));

    msglib::StartTransMessage tx(_name);
    tx.Pack(buffer);

    send(_socket_fd, buffer, 4096, 0);

    recv(_socket_fd, buffer, 4096, 0);

    msglib::ResponseMessage rx;
    rx.Unpack(buffer);

    std::cout << "Asked for: " << rx.requestSent << std::endl;
    std::cout << "Got back: " << rx.response << std::endl;

    // Get a security service with a default config.
    securitylib::ConfigurationGenerator configGenerator;
    securitylib::SecurityConfiguration config = configGenerator.GenerateDefaultConfiguration();

    securitylib::SecurityService service(config);

    // Generate the intermediate keys.
    std::string private_key, public_key;
    service.keyExchangeService->GenerateIntermediateKeys(private_key, public_key);

    // Trade keys.
    // Create the request
    msglib::RequestMessage request_keys("TradeKeys " + public_key, _name);

    request_keys.Pack(buffer);

    send(_socket_fd, buffer, 4096, 0);

    recv(_socket_fd, buffer, 4096, 0);

    rx.Unpack(buffer); // Got keys back.

    _key = service.keyExchangeService->GenerateFinalKey(private_key, rx.response); // Get the exchanged key

    std::string encrypted_message = service.encryptionService->EncryptData(_key, _name, "Hello");
    msglib::EncryptedMessage enc_msg(encrypted_message, _name);
    enc_msg.Pack(buffer);

    send(_socket_fd, buffer, 4096, 0);

    recv(_socket_fd, buffer, 4096, 0);

    enc_msg.Unpack(buffer); // Got message back.
    std::string decrypted_message = service.encryptionService->DecryptData(_key, _name, enc_msg.message);

    std::cout << "Decrypted Message: " << decrypted_message << std::endl;

    // DEBUG: EVERYTHING UNDERNEATH
    // Add some stuff to the queue.

    
    for (int i = 0; i < 10; i++) {
        std::string encryptedMessage = service.encryptionService->EncryptData(_key, _name, "Encrypted message #" + std::to_string(i));
        msglib::EncryptedMessage msg(encrypted_message, _name);
        msg.Pack(buffer);
        std::string packed_data((char*)buffer, 4096);

        {
            std::unique_lock lock(_messageQueueLock);
            _messageQueue.push(packed_data);
        }
    }
}

 void Client::SendQueue() {
    while(_kill_threads.load() != 1) {
        // Wait a second
        std::this_thread::sleep_for(std::chrono::seconds(1));

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

 void Client::Listen() {
    unsigned char buffer[4096];
    memset(buffer, '0', sizeof(buffer));

    while(_kill_threads.load() != 1) {
        // Wait a second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Wait for recv
        recv(_socket_fd, buffer, 4096, 0);

        // Call the handle function.
        HandleIncoming(buffer) ;
    }
 }

 void Client::HandleIncoming(unsigned char* buffer) {

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