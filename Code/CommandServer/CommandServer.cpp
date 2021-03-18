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

// Message lib
#include <MessageLib/IMessage.hpp>
#include <MessageLib/ResponseMessage.hpp>
#include <MessageLib/StartTransMessage.hpp>

// Sec lib
#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>

using namespace std;

CommandServer::CommandServer() {
    // Default constructor
    // Create the security service.
    // Make default config
    securitylib::SecurityConfiguration config;
    config.EncryptionMethod = "AES";
    config.HashingMethod = "SHA3";
    config.KeyExchangeMethod = "Diffie-Helman";
    config.SignatureMethod = "Default";
    config.SymmetricKeyGenerationMethod = "Eliptic-Curve";

    sec_service = make_shared<securitylib::SecurityService>(config);

    sec_service->symmetricKeyGenerationService->GenerateKeys(private_key, public_key);
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
            ci.DH_Serv_PrivKey = "";
            ci.DH_Serv_PubKey = "";

            {
                std::unique_lock lock(client_info_mutex);
                client_info[incoming_msg.name] = ci;
            }
            

            // Need to send back the public key
            msglib::ResponseMessage response("StartTrans", public_key);
            response.Pack((unsigned char*)buffer);
            
            }
            break;
        case 2: // Request
            break;
        default:
            break;
    }
}
