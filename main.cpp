#include "Controller.h"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Usage: ./sniffer <time in seconds> <display packet data (0 or 1)> <testing (0 or 1)>" << endl;
        return -1;
    }

    Controller *controller = new Controller(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    controller->run();
    delete controller;
    return 0;
}