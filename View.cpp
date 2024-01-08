#include "View.h"

View::View()
{
    createFile();
}

View::~View()
{
    delete file;
}

int View::createFile()
{
    file = new ofstream("output.txt");
    if (!file->is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }
    return 0;
}

ofstream& View::getFile()
{
    return *file;
}
