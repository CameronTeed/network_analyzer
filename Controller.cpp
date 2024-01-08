#include "Controller.h"

Controller::Controller(int timeSeconds)
{
    this->timeSeconds = timeSeconds;
    this->model = new Model();
    this->view = new View();
    this->socket = new Socket();
}

Controller::~Controller()
{
    delete this->model;
    delete this->view;
}

void Controller::run()
{
    auto startTime = std::chrono::steady_clock::now();
    auto stopTime = startTime + std::chrono::seconds(timeSeconds);
    auto t1 = Clock::now();

    // ipv4 socket with raw protocol
    socket->createSocket();
    ofstream &out = view->getFile();
    cout << "File created" << endl;

    while (std::chrono::steady_clock::now() < stopTime) {
        cout << "Receiving packets" << endl;
        int recv_bytes = socket->receivePacket();
        cout << "Printing ethernet header" << endl;
        model->print_ethernet_header(out, socket->getBuffer(), recv_bytes);
        cout << "Printing ip header" << endl;
        model->print_ip_header(out, socket->getBuffer(), sizeof(struct ethhdr));
        cout << "Printing protocol" << endl;
        model->protocolSwitch(out, socket->getBuffer());
        cout << "Processing packet" << endl;
        model->processPacket(out, socket->getBuffer(), recv_bytes);
    }

    socket->closeSocket();
}