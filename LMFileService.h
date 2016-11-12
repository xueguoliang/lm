#ifndef LMFILESERVICE_H
#define LMFILESERVICE_H

#include "LM.h"
/* process */
class LMFileService
{
public:
    static LMFileService* instance();
    pid_t _pid;
    int _listenfd;

    void start();
    void sub_process_run();

private:
    LMFileService();
};

#endif // LMFILESERVICE_H
