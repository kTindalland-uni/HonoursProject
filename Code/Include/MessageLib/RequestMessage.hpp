#ifndef __RQSTMSG
#define __RQSTMSG

#include <MessageLib/IMessage.hpp>
#include <string>

namespace msglib {
    class RequestMessage: public IMessage {
        public:
            std::string request;
            std::string name;

            RequestMessage();
            RequestMessage(std::string requestString, std::string clientName);

            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}

#endif