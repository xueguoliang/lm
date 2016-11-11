#ifndef LMCORE_H
#define LMCORE_H

#include "LM.h"

class LMOther
{
public:
    string _name;
    uint32_t _ip;
};

class LMCore
{
public:
    string _name;
    list<uint32_t> _ips;

    // ip is key
    map<uint32_t, LMOther*> _others;

    void add_user(uint32_t ip, string name);

    static LMCore* instance()
    {
        static LMCore* theOne = NULL;
        if(theOne) return theOne;
        return theOne = new LMCore;
    }

private:
    LMCore();
};

#endif // LMCORE_H
