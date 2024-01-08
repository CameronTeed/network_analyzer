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

    while (std::chrono::steady_clock::now() < stopTime) {
        int recv_bytes = socket->receivePacket(socket->getBuffer(), sizeof(socket->getBuffer()));

        model->print_ethernet_header(socket->getBuffer(), recv_bytes);

        model->print_ip_header(socket->getBuffer(), sizeof(struct ethhdr));

        model->protoclSwitch(socket->getBuffer());

        // Print the packet
        model->processPacket(socket->getBuffer(), recv_bytes);
    }

    socket->closeSocket();
}