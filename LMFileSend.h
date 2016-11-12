#ifndef LMFILESEND_H
#define LMFILESEND_H

#include "LM.h"

#define LM_FILE_TYPE_REG 0
#define LM_FILE_TYPE_DIR 1
#define LM_FILE_TYPE_LNK 2
#define LM_FILE_TYPE_OTH 3

class LMFileSend
{
public:
    LMFileSend(int newfd, uint32_t ip);

    pid_t _pid;
    void process_send(int newfd, uint32_t ip);
    void send_file(char* path);

    char* change_cwd(char* path);

    int file_type(char* path);
    uint64_t file_size(char* path);
    void send_reg(char* path, FILE* fp);
    void send_dir(char* path, FILE* fp);

    int _fd;
};

#endif // LMFILESEND_H
