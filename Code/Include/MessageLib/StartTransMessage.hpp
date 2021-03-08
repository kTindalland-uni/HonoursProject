#include <string>
#include <MessageLib/IMessage.hpp>

namespace msglib {
    class StartTransMessage: public IMessage {
        public:
            std::string name;

            StartTransMessage(std::string name);
            StartTransMessage();
            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}