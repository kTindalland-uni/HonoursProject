#include <string>
#include <MessageLib/IMessage.hpp>

namespace msglib {
    class StartTransMessage: public IMessage {
        private:
            int _messageId;
            std::string _name;
        public:
            StartTransMessage(std::string name);
            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}