#include "Formatter.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <vector>
#include <string>

using namespace std;

Formatter::Formatter() {
    setRawMode(true);
}

int Formatter::getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int Formatter::getTerminalHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

string Formatter::centerTextHor(const string& str) {
    int width = getTerminalWidth();
    int padding = (width - str.length()) / 2;
    
    if (padding < 0) {
        padding = 0;
    }

    return string(padding, ' ')+str;
}

void Formatter::printCenteredVer(const vector<string>& lines) {
    int height = getTerminalHeight();
    int numOfLines = lines.size();
    int topPadding = (height - numOfLines) / 2;
    
    for (int i = 0; i < topPadding; ++i) { 
        cout << endl;
    }

    for (int i = 0; i < lines.size(); i++) { 
        cout << lines[i] << endl;
    }
}

void Formatter::printCenteredVerOneLine(const string& str) {
    int height = getTerminalHeight();
    int numOfLines = 1;
    int topPadding = (height - numOfLines) / 2;
    
    for (int i = 0; i < topPadding; ++i) { 
        cout << endl;
    }

    cout << str;
}

void Formatter::setRawMode(bool enable) {
    static termios oldt;
    termios newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable line buffering and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void Formatter::clearScreen() {
    cout << "\033[2J\033[H"; // Clear screen and move cursor to home
}

string Formatter::boldInverted(string& str) {
    return "\033[7;1m"+str+"\033[0m";
}

string Formatter::bold(string& str) {
    return "\033[1m"+str+"\033[0m";
}

string Formatter::boldRed(string& str) {
    return "\033[31;1m"+str+"\033[0m";
}

Formatter::~Formatter() {
    setRawMode(false);
}