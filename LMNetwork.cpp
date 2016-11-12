#include "LMNetwork.h"
#include "LMJson.h"
#include "LMCore.h"
#include "LMFileRecv.h"
LMNetwork *LMNetwork::instance()
{
    static LMNetwork* theOne = NULL;
    if(theOne) return theOne;

    return theOne = new LMNetwork;
}

void *LMNetwork::thread_func(void *ptr)
{
    // recv data
    LMNetwork* This = instance();
    return This->_thread_func(ptr);
}

void *LMNetwork::_thread_func(void *)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    while(1)
    {
        memset(_buf, 0, sizeof(_buf));
        recvfrom(_udpfd, _buf, sizeof(_buf), 0, (struct sockaddr*)&addr, &len);
        list<uint32_t>& ips = LMCore::instance()->_ips;
        auto it = find(ips.begin(), ips.end(), addr.sin_addr.s_addr);
        if(it != ips.end()) // find it, loop
        {
            continue;
        }

        LMJson json;
        if(!json.parse(_buf))
        {
            continue; // drop packet
        }

        string cmd = json.get(LM_CMD);

        if(cmd == LM_ONLINE)
        {
            handle_online(json, addr.sin_addr.s_addr);
        }
        else if(cmd == LM_ONLINEACK)
        {
            handle_online_ack(json, addr.sin_addr.s_addr);
        }
        else if(cmd == LM_SEND)
        {
            handle_send_msg(json);
        }
        else if(cmd==LM_SENDF)
        {
            handle_send_file(json, addr.sin_addr.s_addr);
        }
    }
}

void LMNetwork::send(string msg, uint32_t ip)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LM_PORT_UDP);
    addr.sin_addr.s_addr = ip;

    sendto(this->_udpfd, msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&addr, sizeof(addr));
}

void LMNetwork::handle_online_ack(LMJson &json, uint32_t peerip)
{
    string name = json.get(LM_NAME); // new user name;
    LMCore::instance()->add_user(peerip, name);
}

void LMNetwork::handle_online(LMJson &json, uint32_t peerip)
{
    // save user info
    string name = json.get(LM_NAME); // new user name;
    LMCore::instance()->add_user(peerip, name);

    LMJson resp;
    resp.add(LM_CMD, LM_ONLINEACK);
    resp.add(LM_NAME, LMCore::instance()->_name);

    send(resp.print(), peerip);

}

void LMNetwork::handle_send_msg(LMJson &json)
{
    string name = json.get(LM_NAME);
    string msg = json.get(LM_MSG);

    printf("%s say: %s\n", name.c_str(), msg.c_str());
}

void LMNetwork::handle_send_file(LMJson &json, uint32_t peerip)
{
    string name = json.get(LM_NAME);
    string path = json.get(LM_PATH);

    printf("ready to recv file %s, from %s\n", path.c_str(), name.c_str());

    new LMFileRecv(name, path, peerip);
}

LMNetwork::LMNetwork()
{
    this->_udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LM_PORT_UDP);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(_udpfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        exit(1);
    }

    // allow brocast
    int opt = 1;
    setsockopt(_udpfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    // start thread
    pthread_create(&_tid, NULL, thread_func, NULL);
}
