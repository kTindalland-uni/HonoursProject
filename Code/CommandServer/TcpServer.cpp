#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include <CommandServer/TcpServer.hpp>

#include <MessageLib/StartTransMessage.hpp>

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

        return clientSocket; // Return file descriptor.char buffer[4096];
    }
}