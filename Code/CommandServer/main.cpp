#include <CommandServer/TcpServer.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <CommandServer/CommandServer.hpp>

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Entered main function." << endl;

    auto tcpServer = cmdserv::TcpServer();
    auto cmdServer = CommandServer();

    vector<thread> threads(0);

    while (true) {
        const int clientSocket = tcpServer.Listen();

        thread t(&CommandServer::HandleClientConnection, &cmdServer, clientSocket);

        threads.push_back(move(t));
    }

    for(int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    

    return 0;
}