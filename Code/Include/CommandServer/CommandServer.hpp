#include <memory>
#include <SecurityLib/SecurityService.hpp>
#include <string>

class CommandServer {
    public:
        CommandServer();
        void HandleClientConnection(int socket);
    private:
        void HandleMessage(int messageId);
        std::shared_ptr<securitylib::SecurityService> sec_service;

        std::string public_key;
        std::string private_key;

};