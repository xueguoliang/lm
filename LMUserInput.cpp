#include "LMUserInput.h"
#include "LMUtil.h"
LMUserInput::LMUserInput()
{

}

void LMUserInput::loop()
{
    getcmd();
    handlecmd();
}

void LMUserInput::getcmd()
{
    while(1)
    {
        fgets(_buf, sizeof(_buf), stdin);
        if(strlen(_buf) > 1)
            break;
    }

    // remove \n
    _buf[strlen(_buf)-1] = 0;
}

void LMUserInput::handlecmd()
{
    if(string(_buf) == LM_LIST)
    {
        handlelist();
    }
}

void LMUserInput::handlelist()
{
    LMCore* core = LMCore::instance();

    printf("user list:\n");

    for(auto it = core->_others.begin();
        it != core->_others.end();
        ++it)
    {
        LMOther* other = it->second;
        printf("  %s(%s)\n", other->_name.c_str(), LMUtil::ipaddr(other->_ip).c_str());
        // user list:
        //   xueguoliang(192.168.11.80)
        //   xueguoliang(192.168.11.79)
    }
}


