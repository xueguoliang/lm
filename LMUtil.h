#ifndef LMUTIL_H
#define LMUTIL_H

#include "LM.h"

class LMUtil
{
public:
    LMUtil();

    static char* getHostname();

    static list<uint32_t> getLocalIpAddress();
    static string ipaddr(uint32_t ip);
};

#endif // LMUTIL_H
