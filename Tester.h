#ifndef TESTER_H
#define TESTER_H

#include "Model.h"
#include "View.h"
#include "Socket.h"
#include <gtest/gtest.h>

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