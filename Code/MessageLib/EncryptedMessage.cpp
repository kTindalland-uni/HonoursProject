#include <MessageLib/EncryptedMessage.hpp>

namespace msglib {
    EncryptedMessage::EncryptedMessage() {
        messageId = 3;
        message = "UNDEFINED";
    }

    EncryptedMessage::EncryptedMessage(std::string requestString, std::string messageName) {
        messageId = 3;
        message = requestString;
        name = messageName;
    }

    void EncryptedMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(messageId, buffer, bufferPos);
        IMessage::InsertString(message, buffer, bufferPos);
    }

    void EncryptedMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;

        bufferPos = IMessage::RetrieveInt(&messageId, buffer, bufferPos);
        IMessage::RetrieveString(&message, buffer, bufferPos);
    }
}