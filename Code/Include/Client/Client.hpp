#ifndef CLIENT
#define CLIENT

#include <string>
#include <queue>
#include <mutex>

#include <MessageLib/EncryptedMessage.hpp>

class Client {
    private:
        std::string key;
        std::queue<msglib::EncryptedMessage> messageQueue;

        void HandleIncoming();

    public:
        Client();
        void StartClient();
        void SendQueue(std::mutex& messageQueueLock, std::queue<msglib::EncryptedMessage> messageQueue, int fd);
        void Listen(std::mutex& messageQueueLock, std::queue<msglib::EncryptedMessage> messageQueue, int fd);

};


#endif