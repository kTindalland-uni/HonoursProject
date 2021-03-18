#include <MessageLib/IMessage.hpp>

namespace msglib {
    RequestMessage::RequestMessage() {
        messageId = 2;
        request = "UNDEFINED";
    }

    RequestMessage::RequestMessage(std::string requestString) {
        messageId = 2;
        request = requestString;
    }

    RequestMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(messageId, buffer, bufferPos);
        IMessage::InsertString(request, buffer, bufferPos);
    }

    RequestMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;

        bufferPos = IMessage::RetrieveInt(&messageId, buffer, bufferPos);
        IMessage::RetrieveString(&request, buffer, bufferPos);
    }
}