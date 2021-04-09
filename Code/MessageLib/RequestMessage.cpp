#include <MessageLib/RequestMessage.hpp>

namespace msglib {
    RequestMessage::RequestMessage() {
        messageId = 2;
        request = "UNDEFINED";
    }

    RequestMessage::RequestMessage(std::string requestString, std::string clientName) {
        messageId = 2;
        request = requestString;
        name = clientName;
    }

    void RequestMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(messageId, buffer, bufferPos);
        bufferPos = IMessage::InsertString(request, buffer, bufferPos);
        IMessage::InsertString(name, buffer, bufferPos);
    }

    void RequestMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;

        bufferPos = IMessage::RetrieveInt(&messageId, buffer, bufferPos);
        bufferPos = IMessage::RetrieveString(&request, buffer, bufferPos);
        IMessage::RetrieveString(&name, buffer, bufferPos);
    }
}