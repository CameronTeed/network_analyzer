#define SOCKET_H
#ifdef SOCKET_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>

using namespace std;

class Socket {
    public:
        Socket();
        ~Socket();
        int createSocket();
        int closeSocket();
        int receivePacket(unsigned char *buffer, int size);
        unsigned char* getBuffer();
    private:
        unsigned char buffer[65535];
        int sock;
};

#endif