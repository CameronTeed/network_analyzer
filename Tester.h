#ifndef TESTER_H
#define TESTER_H

#include "Model.h"
#include "View.h"
#include "Socket.h"
#include <gtest/gtest.h>

unsigned char PACKET0[65535] = {"00 de fb 42 50 42 ac d5 64 93 fb 11 86 dd 60 0c \
2e 1d 00 15 06 40 26 20 00 22 40 00 12 01 18 67 \
ff 3e 64 58 5a d7 26 07 f8 b0 40 20 08 07 00 00 \
00 00 00 00 20 0e f5 ee 01 bb 08 ad 7f a7 8a 1c \
fd d7 50 10 01 ff cf db 00 00 00"};
// 23    4.740034    2620:22:4000:1201:1867:ff3e:6458:5ad7    2607:f8b0:4020:807::200e    TCP    75    62958 → 443 [ACK] Seq=1 Ack=1 Win=511 Len=1 [TCP segment of a reassembled PDU]

unsigned char PACKET1[65535] = {};
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

private:

};

#endif