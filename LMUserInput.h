#ifndef LMUSERINPUT_H
#define LMUSERINPUT_H

#include "LMCore.h"

class LMUserInput
{
public:
    LMUserInput();

    char _buf[4096];
    void loop();

    void getcmd();
    void handlecmd();

    void handlelist();
};

#endif // LMUSERINPUT_H
