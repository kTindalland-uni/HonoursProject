#include <CommandServer/CommandServer.hpp>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory>
#include <string>

// Message lib
#include <MessageLib/IMessage.hpp>

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

        HandleMessage(messageId);

    }
}

void CommandServer::HandleMessage(int messageId) {
    cout << "Got here!" << endl;
}
