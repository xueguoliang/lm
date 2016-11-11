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

    void add(string key, string value);
    string print();
    bool parse(char* buf);
    string get(string key);
};

#endif // LMJSON_H
