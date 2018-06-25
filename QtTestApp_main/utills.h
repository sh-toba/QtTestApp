#ifndef UTILLS_H
#define UTILLS_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <tuple>

#define MAX_BUFFER_LENGTH 1024
#define NOINFORMATION string("--")

using namespace std;

namespace Utills {

class NetworkConnectInfo{

public :
    string _conname;
    string _ifname;

    bool _is_dhcp;

    string _ip;
    string _gateway;
    string _dns;

    string _ssid;

    bool _state;

    NetworkConnectInfo();
    NetworkConnectInfo(string conname, string ifname, bool is_dhcp, string ip = NOINFORMATION, string gateway = NOINFORMATION, string dns = NOINFORMATION, string ssid = NOINFORMATION);
    ~NetworkConnectInfo();

    void Set(string conname, string ifname, bool is_dhcp, string ip = NOINFORMATION, string gateway = NOINFORMATION, string dns = NOINFORMATION, string ssid = NOINFORMATION);
    void Show(bool with_header=true);
};

enum NetworkState{
    DISCONNECT,
    CONNECT
};


/* *
 * std::string系 汎用関数群
 *
 * */

// 文字列を二重引用符で囲んで返す
string DoubleQuatationString(string src);
// 文字列分割
void SplitString(string src, const string& delim, vector<string>& result);
// 文字列分割 - 「指定数以上delimが続く」条件で分割する。delimもすべて消去される。
void SplitStringSpecial(string src,  vector<string>& result, const char delim = ' ', const int repeat = 1);
// 文字列合成
string MergeString(const vector<string> src, const string delim);
// vectorリストの表示
void ShowStringVector(const vector<string> src, bool with_no=true);

}

#endif // UTILLS_H
