#include "LMUtil.h"
#include <string.h>
LMUtil::LMUtil()
{

}

char *LMUtil::getHostname()
{
    static char hostname[128] = {0};
    if(strlen(hostname) != 0)
        return hostname;

    FILE* fp = fopen("/etc/hostname", "r");
    fgets(hostname, sizeof(hostname), fp);
    hostname[strlen(hostname)-1] = 0;
    fclose(fp);

    return hostname;
}

list<uint32_t> LMUtil::getLocalIpAddress()
{
    list<uint32_t> ret;
    FILE* fp = popen("ifconfig  | grep inet | grep -v inet6 | awk '{print $2}' | awk -F \":\" '{print $2}'", "r");

    char buf[128];
    while(fgets(buf, sizeof(buf), fp))
    {
        buf[strlen(buf)-1] = 0;
        uint32_t ip = inet_addr(buf);
        ret.push_back(ip);
    }

    pclose(fp);
    return ret;
}