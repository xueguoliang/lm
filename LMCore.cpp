#include "LMCore.h"
#include "LMUtil.h"
void LMCore::add_user(uint32_t ip, string name)
{
    LMLock lock;
    LMOther* other = this->_others[ip];
    if(other)
    {
        other->_name = name;
    }
    else
    {
        other = new LMOther;
        other->_ip = ip;
        other->_name = name;

        this->_others.insert(std::pair<uint32_t, LMOther*>(ip, other));
    }
}

LMCore::LMCore()
{
    _ips = LMUtil::getLocalIpAddress();

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&this->_mutex, &attr);
}

LMLock::LMLock()
{
    pthread_mutex_lock(&LMCore::instance()->_mutex);
}

LMLock::~LMLock()
{
    pthread_mutex_unlock(&LMCore::instance()->_mutex);
}
