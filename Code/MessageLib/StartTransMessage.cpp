#include <string>
#include <MessageLib/StartTransMessage.hpp>

namespace msglib {
    StartTransMessage::StartTransMessage(std::string namearg) {
        messageId = 1;
        name = namearg;
    }

    StartTransMessage::StartTransMessage() {
        messageId = 1;
        name = "UNDEFINED";
    }

    void StartTransMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(messageId, buffer, bufferPos);
        IMessage::InsertString(name, buffer, bufferPos);
    }

    void StartTransMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;

        bufferPos = IMessage::RetrieveInt(&messageId, buffer, bufferPos);
        IMessage::RetrieveString(&name, buffer, bufferPos);
    }
}