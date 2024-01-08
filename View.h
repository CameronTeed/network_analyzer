#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class View
{
public:
    View();
    ~View();
    int createFile();
    ofstream* getFile();
    private:
        ofstream* file;
};

#endif
