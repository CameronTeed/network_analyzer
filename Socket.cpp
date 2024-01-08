#include "Socket.h"

Socket::Socket() {
    cout << "Socket created" << endl;
}

Socket::~Socket() {
    cout << "Socket destroyed" << endl;
}

int Socket::createSocket() {
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (socket < 0) {
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

int Socket::receivePacket(unsigned char *buffer, int size) {

    memset(buffer, 0, sizeof(buffer));
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);
    int recv_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, &saddr, (socklen_t *)&saddr_len);
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