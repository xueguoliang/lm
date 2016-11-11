#ifndef LMJSON_H
#define LMJSON_H

#include <string>
using namespace std;
#include "cJSON.h"
class LMJson
{
public:
    LMJson();
    ~LMJson();

    cJSON* _root;

    // packet
    void add(string key, string value);
    string print();

    // unpacket
    bool parse(char* buf);
    string get(string key);
};

#endif // LMJSON_H
