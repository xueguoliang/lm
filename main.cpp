
#include "LMUserInput.h"
#include "LMNetwork.h"
#include "LMJson.h"
#include "LMUtil.h"
#include "LMFileService.h"

int main(int argc, char* argv[])
{
    // create child process
    LMFileService::instance()->start();

    /* init network module */
    LMNetwork* network = LMNetwork::instance();
    // send broadcast info
    LMJson json;
    json.add(LM_CMD, LM_ONLINE);
    json.add(LM_NAME, LMUtil::getHostname()); /*  read /etc/hostname */
    network->send(json.print());

    LMUserInput input;
    while(1)
    {
        input.loop();
    }

    return 0;
}
