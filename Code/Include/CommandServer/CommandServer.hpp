#include <memory>
#include <SecurityLib/SecurityService.hpp>
#include <string>
#include <map>
#include <CommandServer/ClientInfo.hpp>
#include <shared_mutex>

class CommandServer {
    public:
        CommandServer();
        void HandleClientConnection(int socket);
    private:
        void HandleMessage(int messageId, char* buffer);
        std::shared_ptr<securitylib::SecurityService> sec_service;

        std::string public_key;
        std::string private_key;

        std::shared_mutex client_info_mutex;
        std::map<std::string, ClientInfo> client_info;

};