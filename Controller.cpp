#include "Controller.h"

Controller::Controller(int timeSeconds, int displayData, int testing)
{
    this->timeSeconds = timeSeconds;
    this->displayData = displayData;
    this->testing = testing;
    this->model = new Model(testing);
    this->view = new View();
    this->socket = new Socket();
}

Controller::~Controller()
{
    delete this->model;
    delete this->view;
    delete this->socket;
}

void Controller::run() const
{
    auto startTime = std::chrono::steady_clock::now();
    auto stopTime = startTime + std::chrono::seconds(timeSeconds);
    auto t1 = Clock::now();

    // ipv4 socket with raw protocol
    socket->createSocket();
    ofstream &out = view->getFile();
    //cout << "File created" << endl;

    while (std::chrono::steady_clock::now() < stopTime) {
        //cout << "Receiving packets" << endl;
        int recv_bytes = socket->receivePacket();
        //cout << "Printing ethernet header" << endl;
        model->print_ethernet_header(out, socket->getBuffer(), recv_bytes);
       // cout << "Printing ip header" << endl;
        model->print_ip_header(out, socket->getBuffer(), sizeof(struct ethhdr));
        //cout << "Printing protocol" << endl;
        model->protocolSwitch(out, socket->getBuffer());
        //cout << "Processing packet" << endl;
        if (displayData == 1)
        model->processPacket(out, socket->getBuffer(), recv_bytes);
    }

    socket->closeSocket();
}