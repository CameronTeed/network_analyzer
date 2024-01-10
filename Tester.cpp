#include "Tester.h"


Tester::Tester()
{

}

void Tester::run()
{
    testSocket();
    testView();
    testModel();
}

void Tester::testSocket()
{
    Socket *s = new Socket();
    EXPECT_GT(s->createSocket(), -1) << "Socket creation failed";
    EXPECT_GT(s->closeSocket(), -1) << "Socket creation failed";
}

void Tester::testModel() {
    Model * m = new Model();
    m->print_ethernet_header(v->getFile(), PACKET0, sizeof(EthernetHeader));
}

void Tester::testView() {
    v = new View();
}

int main(int argc, char **argv) {
    Tester*t = new Tester();
    t->run();
    return 0;
}

void Tester::initPacket0() {
// Initialize fake Ethernet header
    memset(PACKET0, 0, sizeof(PACKET0));
    // Type cast structures and copy their data to PACKET0
    struct EthernetHeader* ethHeader = (struct EthernetHeader*)PACKET0;
    struct IPHeader* ipHeader = (struct IPHeader*)(PACKET0 + sizeof(struct EthernetHeader));
    struct TCPPacket* tcpPacket = (struct TCPPacket*)(PACKET0 + sizeof(struct EthernetHeader) + sizeof(struct IPHeader));

    // Populate fake Ethernet header
    memcpy(ethHeader->destinationMAC, "\x00\x11\x22\x33\x44\x55", 6);  // Fake destination MAC
    memcpy(ethHeader->sourceMAC, "\xAA\xBB\xCC\xDD\xEE\xFF", 6);  // Fake source MAC
    ethHeader->etherType = 0x0800;  // IPv4

    // Populate fake IP header
    ipHeader->versionIHL = 0x45;  // IPv4, 20-byte header length
    ipHeader->typeOfService = 0;
    ipHeader->totalLength = sizeof(struct IPHeader) + sizeof(struct TCPPacket);
    ipHeader->identification = 0;
    ipHeader->flagsFragmentOffset = 0;
    ipHeader->timeToLive = 128;
    ipHeader->protocol = 0x06;  // TCP
    ipHeader->headerChecksum = 0;  // You may need to calculate the checksum based on the actual data
    ipHeader->sourceIP = inet_addr("192.168.1.2");  // Fake source IP
    ipHeader->destinationIP = inet_addr("192.168.1.3");  // Fake destination IP

    // Populate fake TCP packet
    tcpPacket->sourcePort = 1234;  // Source port
    tcpPacket->destinationPort = 5678;  // Destination port
    tcpPacket->sequenceNumber = 0;
    tcpPacket->acknowledgmentNumber = 0;
    tcpPacket->dataOffsetAndFlags = 0x50;  // Assuming no options, and SYN flag set
    tcpPacket->windowSize = 1024;
    tcpPacket->checksum = 0;  // You may need to calculate the checksum based on the actual data
    tcpPacket->urgentPointer = 0;

    // Insert payload data
    const char* payloadData = "This is a test TCP packet.";
    strncpy((char*)tcpPacket->payload, payloadData, sizeof(tcpPacket->payload));

}