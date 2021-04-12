#include <CommandServer/CommandServer.hpp>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory>
#include <string>
#include <unistd.h>
#include <CommandServer/ClientInfo.hpp>
#include <mutex>
#include <shared_mutex>
#include <vector>

// Message lib
#include <MessageLib/IMessage.hpp>
#include <MessageLib/ResponseMessage.hpp>
#include <MessageLib/StartTransMessage.hpp>
#include <MessageLib/RequestMessage.hpp>
#include <MessageLib/EncryptedMessage.hpp>

// Sec lib
#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <SecurityLib/ConfigurationGenerator.hpp>

#include <iostream>

using namespace std;

CommandServer::CommandServer() {
    // Default constructor
    // Create the security service.
    // Make default config
    securitylib::ConfigurationGenerator config_generator;
    securitylib::SecurityConfiguration config = config_generator.GenerateDefaultConfiguration();

    sec_service = make_shared<securitylib::SecurityService>(config);

    sec_service->symmetricKeyGenerationService->GenerateKeys(private_key, public_key);
    sec_service->keyExchangeService->GenerateIntermediateKeys(KE_private_key, KE_public_key);
}

void CommandServer::HandleClientConnection(int socket) {
    int const bufferLen = 4096;
    char buffer[bufferLen];

    while (true) {
        memset(buffer, 0, 4096);

        // Wait for client to send data.
        int bytesReceived = recv(socket, buffer, bufferLen, 0);
        if (bytesReceived == -1) {
            cerr << "Error in recv()." << endl;
            break;
        }

        if (bytesReceived == 0) {
            cout << "Client disconnected." << endl;
            break;
        }

        cout << "Received bytes" << endl;

        int messageId;
        msglib::IMessage::RetrieveInt(&messageId, (unsigned char*)buffer, 0);

        cout << messageId << endl;

        HandleMessage(messageId, buffer);

        send(socket, buffer, bufferLen, 0);
    }

    close(socket);
}

void CommandServer::HandleMessage(int messageId, char* buffer) {
    switch (messageId) {
        case 1: {// Start transaction message

            // Take the name from the start trans msg
            msglib::StartTransMessage incoming_msg;
            incoming_msg.Unpack((unsigned char*)buffer);

            ClientInfo ci;
            ci.KE_key = "";

            {
                std::unique_lock lock(client_info_mutex);
                client_info[incoming_msg.name] = ci;
            }
            

            // Need to send back the public key
            msglib::ResponseMessage response("StartTrans", public_key);
            response.Pack((unsigned char*)buffer);
            
            }
            break;

        case 2: {// Request
            msglib::RequestMessage incoming_msg;
            incoming_msg.Unpack((unsigned char*)buffer);

            std::string request = incoming_msg.request.substr(0, 10);
            if (request == "TradeKeys ") {
                // Get the key out of it
                std::string client_public_key = incoming_msg.request.substr(10);
                // Perform the key exchange

                std::string key = sec_service->keyExchangeService->GenerateFinalKey(KE_private_key, client_public_key);

                // Store the key
                {
                    std::unique_lock lock(client_info_mutex);
                    client_info[incoming_msg.name].KE_key = key;
                }

                // Craft and Send the response.
                msglib::ResponseMessage response("TradeKeys", KE_public_key);

                response.Pack((unsigned char*)buffer);
            }

            }
            break;

        case 4: { // Encrypted Message
            msglib::EncryptedMessage incoming_msg;
            incoming_msg.Unpack((unsigned char*)buffer);

            // Get the key from the store
            std::string key;
            {
                std::shared_lock lock_shared(client_info_mutex); // Lock for read-only
                key.assign(client_info[incoming_msg.name].KE_key);
            }

            std::string decrypted_message = sec_service->encryptionService->DecryptData(key, incoming_msg.name, incoming_msg.message);

            // Get the message type
            std::string message_request = decrypted_message.substr(0, 10);

            // Switch on the message_request
            if (message_request == "StatusUpd ") {
                // Params in one string
                std::string params = decrypted_message.substr(10);
                
                // Extract the params
                vector<string> params_vec;
                SplitString(params, ',', params_vec);

                // Map the params
                {
                    unique_lock lock(_client_statuses_mutex);
                    vector<string> single_param;
                    for (int i = 0; i < params_vec.size(); i++) {
                        SplitString(params_vec[i], '=', single_param);
                        _client_statuses[incoming_msg.name][single_param[0]] = single_param[1];

                    }
                }
                

            }


            // Iterate over map and print
            map<string, string> client_status;
            {
                unique_lock lock(_client_statuses_mutex);

                client_status = _client_statuses[incoming_msg.name];
            }
            map<string, string>::iterator iter = client_status.begin();

            for(pair<string, string> element : client_status) {
                cout << element.first << ": " << element.second << endl;
            }


            // Encrypt and send back

            std::string encrypted_message = sec_service->encryptionService->EncryptData(key, incoming_msg.name, decrypted_message);
            msglib::EncryptedMessage response(encrypted_message, "Server");

            response.Pack((unsigned char*)buffer);

            }
            break;

        default:
            break;
    }
}

// Split string method from https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s07.html
void CommandServer::SplitString(const string& s, char c, vector<string>& v) {
    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}