#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <iomanip>
#include <netinet/udp.h>
#include <netinet/tcp.h>

using namespace std;

class Model {

public:
    Model();
    ~Model();
    void processPacket(unsigned char *buffer, int size);
    void print_ethernet_header(unsigned char *buffer, int size);
    void print_ip_header(unsigned char *buffer, int size);
    void printProtocol(int prot);
    void print_udp_header(unsigned char *buffer, int size);
    void print_tcp_header(unsigned char *buffer, int size);
    void protoclSwitch(unsigned char *buffer);

private:

};


#endif