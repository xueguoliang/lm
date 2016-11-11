#ifndef LMUTIL_H
#define LMUTIL_H

#include "LM.h"

class LMUtil
{
public:
    LMUtil();

    static char* getHostname();

    static list<uint32_t> getLocalIpAddress();
};

#endif // LMUTIL_H
