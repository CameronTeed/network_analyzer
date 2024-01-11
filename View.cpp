#include "View.h"

View::View()
{
    createFile();
}

View::View(int i = 0) {
    createFileApp();
}

View::~View()
{
    delete file;
}

int View::createFile()
{
    file = new ofstream("output.txt");
    if (!file->is_open()) {
        cerr  << "Error opening file" << endl;
        return -1;
    }
    return 0;
}

int View::createFileApp()
{
    file = new ofstream("output.txt", ios::out | ios::app );
    if (!file->is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }
    return 0;
}

ofstream& View::getFile() const
{
    return *file;
}