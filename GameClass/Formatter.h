#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <vector>
#include <string>

using namespace std;

class Formatter {

    public:
        Formatter();
        int getTerminalWidth();
        int getTerminalHeight();
        
        string centerTextHor(const string& str);
        void printCenteredVer(const vector<string>& lines);
        void printCenteredVerOneLine(const string& str);
        
        void setRawMode(bool enable);
        void clearScreen();

        string boldInverted(string& str);
        string bold(string& str);
        string boldRed(string& str);

        ~Formatter();

    protected:

};

#endif