
#include "LMUserInput.h"
#include "LMNetwork.h"
#include "LMJson.h"
#include "LMUtil.h"

int main(int argc, char* argv[])
{
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
