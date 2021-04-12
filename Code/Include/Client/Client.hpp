#ifndef CLIENT
#define CLIENT

#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <vector>
#include <thread>
#include <condition_variable>
#include <memory>

#include <MessageLib/EncryptedMessage.hpp>

#include <SecurityLib/SecurityService.hpp>

class Client {
    private:
        std::string _key; // The encryption key used to encrypt and decrypt messages.
        std::string _name; // Name of the client
        std::string _server_sign_key; // Server public key
        std::string _server_pub_key;

        std::queue<std::string> _messageQueue; // Stores encrypted messages to be sent to the server.
        std::mutex _messageQueueLock; // Used to lock the message queue. To be able to use the queue on multiple threads.
        
        std::condition_variable _get_keys_cv;
        std::mutex _get_keys_mutex;

        std::atomic<unsigned char> _kill_threads; // Make 1 when you want to stop the threads from executing.
        std::atomic<unsigned char> _is_running;
        std::atomic<unsigned char> _can_encrypt;

        std::vector<std::thread> _threads;

        std::shared_ptr<securitylib::SecurityService> _sec_service;

        int _socket_fd; // The file descriptor of the socket used to communicate with the server.

        void HandleIncoming(unsigned char* buffer); // Handles incoming messages from the server.
        void SendQueue();
        void Listen();
        void AddBufferToQueue(unsigned char* buffer, int length);
        void GetEncryptionKeysWithQueue();
        void SendStatusUpdatesThreadFunction();
    public:
        Client();
        void StartClient();
        void GetEncryptionKeys();
        void StartCommunicationThreads();
        void KillCommunicationThreads();
        bool IsRunning();
        void StopAll();
        void SendStatusUpdates();
        
};


#endif