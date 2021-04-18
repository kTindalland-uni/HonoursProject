#include <iostream>
#include <string>
#include <chrono>
#include <Client/Client.hpp>


// For signal processing...
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

Client client;

void sigint_handler(int signum) {
    std::cout << "\nCaught SIGINT, stopping gracefully." << std::endl;

    client.StopAll();
}

int main(int argc, char** argv)
{
    
    // Register the signal interrupt.
    signal(SIGINT, sigint_handler);

    // Spin up the client
    std::string name = "Un-named_client";
    if (argc > 1) {
        name = std::string(argv[1]);
    }
    client.StartClient(name);
    client.StartCommunicationThreads();
    client.GetEncryptionKeys();

    client.SendStatusUpdates();

    while(client.IsRunning()) {
        // Wait to not max out CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
 
    return 0;
}