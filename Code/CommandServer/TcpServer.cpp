#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include <CommandServer/TcpServer.hpp>

using namespace std;

namespace cmdserv {

    TcpServer::TcpServer() {
        // Create a listening socket
        listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listeningSocket == -1) { // Check for errors
            cerr << "Can't create a socket." << endl;
        }

        // Bind ip addr and port to socket
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(56000); // Host to network short
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // Char Pointer to numbers

        bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));

        // Mark the socket is for listening
        listen(listeningSocket, SOMAXCONN);
    }

    TcpServer::~TcpServer() {
        close(listeningSocket);
    }

    int TcpServer::Listen() {
        // Wait for connection
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(listeningSocket, (sockaddr*)&client, &clientSize);

        char host[NI_MAXHOST]; // Client's remote name
        char service[NI_MAXSERV]; // Service (port) the client is connected on.

        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            cout << host << " connected on port " << service << endl;
        }
        else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on port " << ntohs(client.sin_port) << endl;
        }

        

        return clientSocket; // Return file descriptor.char buffer[4096];
    }

    void TcpServer::EchoTest(int clientSocket) {
        char buffer[4096];

        while(true) {
            memset(buffer, 0, 4096);

            // Wait for client to send data.
            int bytesReceived = recv(clientSocket, buffer, 4096, 0);
            if (bytesReceived == -1) {
                cerr << "Error in recv()." << endl;
                break;
            }

            if (bytesReceived == 0) {
                cout << "Client disconnected." << endl;
                break;
            }

            string receivedText(buffer, 0, bytesReceived);

            if (receivedText.compare(0, 11, "Hello there") == 0) {
                cout << "General Kenobi" << endl;
            }
            else  {
                cout << "Received: " << receivedText << endl;
            }

            // Echo message back.
            send(clientSocket, buffer, bytesReceived + 1, 0);
        }
    }
}