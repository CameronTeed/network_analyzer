#include "Socket.h"

Socket::Socket() {
}

Socket::~Socket() {
}

int Socket::createSocket() {
    sock = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));;
    if (sock < 0) {
        cout << "Socket creation failed" << endl;
        return -1;
    }
    cout << "Socket created" << endl;
    return sock;
}

int Socket::closeSocket() {
    if (close(sock) < 0) {
        cout << "Socket close failed" << endl;
        return -1;
    }
    cout << "Socket closed" << endl;
    return 0;
}

// I think because im using wsl, there alot of udp being sent, will try in vm
int Socket::receivePacket() {
    
    memset(buffer, 0, sizeof(buffer));
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);
    int recv_bytes = recvfrom(sock,buffer,65535,0,&saddr,(socklen_t *)&saddr_len);
    if (recv_bytes < 0) {
        cout << "Error receiving packet" << endl;
        return -1;
    }
    cout << "Packet received" << endl;
    return recv_bytes;
}

unsigned char* Socket::getBuffer() {
    return buffer;
}