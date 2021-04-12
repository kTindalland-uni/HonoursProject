#include <memory>
#include <SecurityLib/SecurityService.hpp>
#include <string>
#include <map>
#include <CommandServer/ClientInfo.hpp>
#include <shared_mutex>
#include <vector>

class CommandServer {
    public:
        CommandServer();
        void SplitString(const std::string& s, char c, std::vector<std::string>& v);
        void HandleClientConnection(int socket);

        std::shared_mutex _client_statuses_mutex;
        std::map<std::string, std::map<std::string, std::string>> _client_statuses;
    private:
        void HandleMessage(int messageId, char* buffer);
        std::shared_ptr<securitylib::SecurityService> sec_service;

        std::string public_key;
        std::string private_key;

        std::string KE_public_key;
        std::string KE_private_key;

        std::shared_mutex client_info_mutex;
        std::map<std::string, ClientInfo> client_info;

};