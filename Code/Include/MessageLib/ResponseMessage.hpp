#ifndef __RESPMSG
#define __RESPMSG

#include <MessageLib/IMessage.hpp>
#include <string>

namespace msglib {
    class ResponseMessage: public IMessage {
        public:
            std::string requestSent;
            std::string response;

            ResponseMessage();
            ResponseMessage(std::string requestString, std::string responseString);

            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}

#endif