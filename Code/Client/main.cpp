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
#include <iostream>
 
int main()
{
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
 
    msglib::StartTransMessage tx("Hello world");
    tx.Pack(buffer);

    send(CreateSocket, buffer, 4096, 0);

    recv(CreateSocket, buffer, 4096, 0);

    msglib::ResponseMessage rx;
    rx.Unpack(buffer);

    std::cout << "Asked for: " << rx.requestSent << std::endl;
    std::cout << "Got back: " << rx.response << std::endl;

    while (true) {
        
    }

    close(CreateSocket);
 
    return 0;
}