#ifndef LMNETWORK_H
#define LMNETWORK_H

#include "LMCore.h"
#include "LM.h"

class LMNetwork
{
public:
    static LMNetwork* instance();

    /* send msg, brocast msg */
    int _udpfd;
    pthread_t _tid;
    char _buf[4096];

    static void* thread_func(void* ptr);
    void* _thread_func(void*);

    // send broadcast
    void send(string msg, uint32_t ip=0xffffffff);

private:
    LMNetwork();
};

#endif // LMNETWORK_H