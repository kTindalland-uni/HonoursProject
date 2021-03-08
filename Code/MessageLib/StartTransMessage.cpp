#include <string>
#include <MessageLib/StartTransMessage.hpp>

namespace msglib {
    StartTransMessage::StartTransMessage(std::string name) {
        _messageId = 1;
        _name = name;
    }

    void StartTransMessage::Pack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::InsertInt(_messageId, buffer, bufferPos);
        IMessage::InsertString(_name, buffer, bufferPos);
    }

    void StartTransMessage::Unpack(unsigned char* buffer) {
        int bufferPos = 0;
        
        bufferPos = IMessage::RetrieveInt(&_messageId, buffer, bufferPos);
        IMessage::RetrieveString(&_name, buffer, bufferPos);
    }
}