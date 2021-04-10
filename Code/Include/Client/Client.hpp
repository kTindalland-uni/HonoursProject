#ifndef CLIENT
#define CLIENT

#include <string>
#include <queue>
#include <mutex>
#include <atomic>

#include <MessageLib/EncryptedMessage.hpp>

class Client {
    private:
        std::string _key; // The encryption key used to encrypt and decrypt messages.
        std::string _name; // Name of the client

        std::queue<std::string> _messageQueue; // Stores encrypted messages to be sent to the server.
        std::mutex _messageQueueLock; // Used to lock the message queue. To be able to use the queue on multiple threads.
        
        std::atomic<unsigned char> _kill_threads; // Make 1 when you want to stop the threads from executing.

        int _socket_fd; // The file descriptor of the socket used to communicate with the server.

        void HandleIncoming(); // Handles incoming messages from the server.
        void SendQueue();
        void Listen();
    public:
        Client();
        void StartClient();
        void GetEncryptionKeys();
        void StartCommunicationThreads();
        void KillCommunicationThreads();
        

};


#endif