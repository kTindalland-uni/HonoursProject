#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include <MessageLib/StartTransMessage.hpp>
#include <MessageLib/ResponseMessage.hpp>
#include <MessageLib/RequestMessage.hpp>
#include <MessageLib/EncryptedMessage.hpp>

#include <SecurityLib/ConfigurationGenerator.hpp>
#include <SecurityLib/SecurityService.hpp>
#include <SecurityLib/Structures/SecurityConfiguration.hpp>
#include <iostream>
#include <string>

#include <thread>
#include <chrono>
 
int main()
{
    std::string name = "Client1";
    int CreateSocket = 0,n = 0;
    unsigned char buffer[4096];
    struct sockaddr_in ipOfServer;
 
    memset(buffer, '0' ,sizeof(buffer));
 
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
 
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(56000);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
 
    msglib::StartTransMessage tx(name);
    tx.Pack(buffer);

    send(CreateSocket, buffer, 4096, 0);

    recv(CreateSocket, buffer, 4096, 0);

    msglib::ResponseMessage rx;
    rx.Unpack(buffer);

    std::cout << "Asked for: " << rx.requestSent << std::endl;
    std::cout << "Got back: " << rx.response << std::endl;

    // Get a security service with a default config.
    securitylib::ConfigurationGenerator configGenerator;
    securitylib::SecurityConfiguration config = configGenerator.GenerateDefaultConfiguration();

    securitylib::SecurityService service(config);

    // Generate the intermediate keys.
    std::string private_key, public_key;
    service.keyExchangeService->GenerateIntermediateKeys(private_key, public_key);

    // Trade keys.
    // Create the request
    msglib::RequestMessage request_keys("TradeKeys " + public_key, name);

    request_keys.Pack(buffer);

    send(CreateSocket, buffer, 4096, 0);

    recv(CreateSocket, buffer, 4096, 0);

    rx.Unpack(buffer); // Got keys back.

    std::string key = service.keyExchangeService->GenerateFinalKey(private_key, rx.response); // Get the exchanged key

    std::string encrypted_message = service.encryptionService->EncryptData(key, name, "Hello");
    msglib::EncryptedMessage enc_msg(encrypted_message, name);
    enc_msg.Pack(buffer);

    send(CreateSocket, buffer, 4096, 0);

    recv(CreateSocket, buffer, 4096, 0);

    enc_msg.Unpack(buffer); // Got message back.
    std::string decrypted_message = service.encryptionService->DecryptData(key, name, enc_msg.message);

    std::cout << "Decrypted Message: " << decrypted_message << std::endl;

    close(CreateSocket);
 
    return 0;
}

void SendStatusUpdate() {

    // Send 10 status updates
    for(int i = 0; i < 10; i++) {

        // Create and pack a message.
        

        // Wait for 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}