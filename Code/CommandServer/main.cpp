#include <CommandServer/TcpServer.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Entered main function." << endl;

    auto tcpServer = cmdserv::TcpServer();

    int clientSocket = tcpServer.Listen();

    tcpServer.EchoTest(clientSocket);

    return 0;
}