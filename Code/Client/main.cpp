#include <iostream>
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

int main()
{
    // Register the signal interrupt.
    signal(SIGINT, sigint_handler);

    // Spin up the client    
    client.StartClient();
    client.StartCommunicationThreads();
    client.GetEncryptionKeys();

    client.SendStatusUpdates();

    while(client.IsRunning()) {
        // Wait to not max out CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
 
    return 0;
}

void SendStatusUpdate() {

    // Send 10 status updates
    for(int i = 0; i < 10; i++) {

        // Create and pack a message.
        

        // Wait for 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}