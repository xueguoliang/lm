#ifndef LMFILERECV_H
#define LMFILERECV_H

#include "LM.h"

class LMFileRecv
{
public:
    LMFileRecv(string peername, string path, uint32_t peerip);

    pthread_t _tid;

    string _peername;
    string _peerpath;
    uint32_t _peerip;

    static void* thread_func(void* arg);
    void run();
    void recv_file(int fd);
    char _buf[1024];

    char* get_line(FILE* fp);
};

#endif // LMFILERECV_H
