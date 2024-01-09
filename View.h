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
    ofstream& getFile();
    private:
        int createFile();
        ofstream* file;
};

#endif
