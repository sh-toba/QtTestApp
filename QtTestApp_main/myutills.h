#ifndef MYUTILLS_H
#define MYUTILLS_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace Utills {

struct NetworkConnectInfo{
    string name;
    string type;
    bool is_dhcp;
    string ip;
    string gateway;
    string dns;
    string ssid;
};

enum NetworkState{
    DISCONNECTED,
    CONNECTED_Eth,
    CONNECTED_Wifi,
    CONNECTION_FAILED
};

// 文字を二重引用符で囲んで返す
string DoubleQuatationString(string src);

void SplitString(const string& src, const string& delim, vector<string>& result);


}

#endif // MYUTILLS_H
