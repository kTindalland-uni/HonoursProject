#include <CommandServer/TcpServer.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <CommandServer/CommandServer.hpp>

// For signal processing...
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

using namespace std;

void sigint_handler(int signum) {
    std::cout << "\nCaught SIGINT. Not stopping, please use the 'quit' command to exit the CommandServer." << std::endl;
}

int main(int argc, char *argv[]) {

    cout << "Server Starting..." << endl;

    auto tcpServer = cmdserv::TcpServer();
    auto cmdServer = CommandServer();

    

    vector<thread> threads(0);

    cout << "Server Started. Listening for clients." << endl;

    thread cmd_thread = cmdServer.RunCommandThread();

    while (cmdServer.IsRunning()) {
        const int clientSocket = tcpServer.Listen();

        thread t(&CommandServer::HandleClientConnection, &cmdServer, clientSocket);

        threads.push_back(move(t));
    }

    for(int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    

    return 0;
}