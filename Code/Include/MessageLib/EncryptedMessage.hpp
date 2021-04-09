#ifndef __ENCMSG
#define __ENCMSG

#include <MessageLib/IMessage.hpp>
#include <string>

namespace msglib {
    class EncryptedMessage: public IMessage {
        public:
            std::string message;
            std::string name;

            EncryptedMessage();
            EncryptedMessage(std::string message, std::string name);

            void Pack(unsigned char* buffer);
            void Unpack(unsigned char* buffer);
    };
}

#endif