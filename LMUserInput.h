#ifndef LMUSERINPUT_H
#define LMUSERINPUT_H

#include "LMCore.h"

class LMUserInput
{
public:
    LMUserInput();

    char _buf[4096];
    vector<string> _args;

    void loop();

    void getcmd();
    void splitcmd();
    void handlecmd();

    void handlelist();
    void handlesend();
};

#endif // LMUSERINPUT_H
