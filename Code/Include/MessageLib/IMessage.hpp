#include <cstring>
#include <string>

namespace msglib {
    class IMessage {
        public:
            int messageId;
            virtual void Pack(unsigned char* buffer) = 0;
            virtual void Unpack(unsigned char* buffer) = 0;

            static int InsertInt(int number, unsigned char* buffer, int index) {
                std::memcpy(&buffer[index], &number, sizeof( int ));

                return sizeof(int) + index; // returns next index
            }

            static int RetrieveInt(int* result, unsigned char* buffer, int index) {
                std::memcpy(result, &buffer[index], sizeof( int ) );

                return sizeof(int) + index;
            }

            static int InsertString(std::string data, unsigned char* buffer, int index) {
                int length = data.size();
                index = IMessage::InsertInt(length, buffer, index);

                data.copy((char*)&buffer[index], length, 0);

                return index + length;
            }

            static int RetrieveString(std::string* data, unsigned char* buffer, int index) {
                int length;
                index = IMessage::RetrieveInt(&length, buffer, index);

                std::string result((char*)&buffer[index], length);

                *data = result;

                return index + length;
            }
    };
}