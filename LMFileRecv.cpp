#include "LMFileRecv.h"

LMFileRecv::LMFileRecv(string peername, string path, uint32_t peerip)
{
    _peername = peername;
    _peerpath = path;
    _peerip = peerip;
    pthread_create(&_tid, NULL, thread_func, this);
}

void *LMFileRecv::thread_func(void *arg)
{
    LMFileRecv* This = (LMFileRecv*)arg;
    This->run();
}

void LMFileRecv::run()
{
    // send path --> peer
    // recv content
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LM_PORT_TCP);
    addr.sin_addr.s_addr = _peerip;

    connect(fd, (struct sockaddr*)&addr, sizeof(addr));

    write(fd, _peerpath.c_str(), strlen(_peerpath.c_str()));
    write(fd, "\n", 1);

    recv_file();
}

void LMFileRecv::recv_file()
{

}
