#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "View.h"
#include <chrono>
#include "Socket.h"

class Controller
{   
public:
    Controller(int timeSeconds, int displayData, int testing);
    ~Controller();
    void run() const;
private:
    typedef std::chrono::high_resolution_clock Clock;
    Model *model;
    View *view;
    Socket *socket;
    int timeSeconds;
    int displayData;
    int testing;
};



#endif