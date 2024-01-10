#ifndef TESTER_H
#define TESTER_H

#include "Model.h"
#include "View.h"
#include "Socket.h"
#include <gtest/gtest.h>

// IP header structure
struct IPHeader {
    unsigned char versionIHL;  // Version (4 bits) + Internet Header Length (4 bits)
    unsigned char typeOfService;
    unsigned short totalLength;
    unsigned short identification;
    unsigned short flagsFragmentOffset;
    unsigned char timeToLive;
    unsigned char protocol;
    unsigned short headerChecksum;
    unsigned int sourceIP;
    unsigned int destinationIP;
};

// Ethernet header structure
struct EthernetHeader {
    unsigned char destinationMAC[6];
    unsigned char sourceMAC[6];
    unsigned short etherType;
};

struct TCPPacket {
    unsigned short sourcePort;
    unsigned short destinationPort;
    unsigned int sequenceNumber;
    unsigned int acknowledgmentNumber;
    unsigned char dataOffsetAndFlags;
    unsigned short windowSize;
    unsigned short checksum;
    unsigned short urgentPointer;
    unsigned char payload[1500];  // Adjust the size based on your needs
};

unsigned char PACKET0[65535];
// 23    4.740034    2620:22:4000:1201:1867:ff3e:6458:5ad7    2607:f8b0:4020:807::200e    TCP    75    62958 → 443 [ACK] Seq=1 Ack=1 Win=511 Len=1 [TCP segment of a reassembled PDU]

unsigned char* PACKET1[65535];
unsigned char PACKET2[65535] = {};


class Tester
{
public:
    Tester();
    ~Tester();
    void run();
    void testSocket();
    void testModel();
    void testView();

    void testEth();
    void testIP();
    void testTCP();
    void testUDP();
    void testPayload();
    void initPacket0();

private:
    View* v;
};

#endif