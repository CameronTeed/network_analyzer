#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<linux/if_packet.h>
#include<netinet/in.h>	
#include <net/ethernet.h>
#include<netinet/if_ether.h> 
#include <net/if.h>
#include <iomanip>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <fstream>

using namespace std;

class Model {

public:
    Model();
    Model(int testing);
    ~Model();
    void processPacket(ofstream&  out, unsigned char *buffer, int size) const;
    void print_ethernet_header(ofstream&  out, unsigned char *buffer, int size) const;
    void print_ip_header(ofstream&  out, unsigned char *buffer, int size);
    void printProtocol(ofstream&  out, int prot) const;
    void protocolSwitch(ofstream&  out, unsigned char *buffer);

private:
    unsigned int protocol;
    int testing;

    void print_udp_header(ofstream&  out, unsigned char *buffer, int size) const;
    void print_tcp_header(ofstream&  out, unsigned char *buffer, int size) const;
};


#endif