#include "Controller.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: ./sniffer <time in seconds>" << endl;
        return -1;
    }

    Controller *controller = new Controller(atoi(argv[1]));
    controller->run();
    delete controller;
    return 0;
}