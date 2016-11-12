#ifndef LMFILESERVICE_H
#define LMFILESERVICE_H

#include "LM.h"
#include "LMFileSend.h"
/* process */
class LMFileService
{
public:
    static LMFileService* instance();
    pid_t _pid;
    int _listenfd;

    void start();
    void sub_process_run();

    static void child_process_end(int sig);

    map<pid_t, LMFileSend*> _fileSendingProcess;

    bool _bChildProcessEnd;

private:
    LMFileService();
};

#endif // LMFILESERVICE_H
