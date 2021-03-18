#include <MessageLib/ResponseMessage.hpp>
#include <string>

namespace msglib {
    ResponseMessage::ResponseMessage() {
        messageId = 3;
        requestSent = "UNDEFINED"
        response = "UNDEFINED";
    }

    ResponseMessage::ResponseMessage(std::string requestString, std::string responseString) {
        messageId = 3;
        requestSent = requestString;
        response = responseString;
    }

    ResponseMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(messageId, buffer, bufferPos);
        bufferPos = IMessage::InsertString(requestSent, buffer, bufferPos);
        IMessage::InsertString(response, buffer, bufferPos);
    }

    ResponseMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;

        bufferPos = IMessage::RetrieveInt(&messageId, buffer, bufferPos);
        bufferPos = IMessage::RetrieveString(&requestSent, buffer, bufferPos);
        IMessage::RetrieveString(&response, buffer, bufferPos);
    }
}