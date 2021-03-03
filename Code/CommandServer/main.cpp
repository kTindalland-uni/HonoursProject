#include <CommandServer/TcpServer.hpp>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void EchoTest();

int main(int argc, char *argv[]) {

    cout << "Entered main function." << endl;

    auto tcpServer = cmdserv::TcpServer();

    vector<thread> threads(5);

    while (true) {
        const int clientSocket = tcpServer.Listen();

        thread t(EchoTest);

        threads.push_back(move(t));
    }

    for(int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    // tcpServer.EchoTest(clientSocket);

    return 0;
}

void EchoTest() {
    cout << "Hello world! Socket ID:" << endl;
}
