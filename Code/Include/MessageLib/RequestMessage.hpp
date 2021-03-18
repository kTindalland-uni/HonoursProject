#include <MessageLib/IMessage.hpp>
#include <string>

namespace msglib {
    class RequestMessage: public IMessage {
        public:
            std::string request;

            RequestMessage();
            RequestMessage(std::string requestString);

            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}