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

using namespace std;

namespace Utills {

struct NetworkConnectInfo{
    string conname;
    bool state;
    string ifname;
    bool is_dhcp;
    string ip;
    string gateway;
    string dns;
    string ssid;

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
void SplitString(const string& src, const string& delim, vector<string>& result);
// 文字列合成
string MergeString(const vector<string> src, const string delim);
// vectorリストの表示
void ShowStringVector(const vector<string> src, bool with_no=true);

}

#endif // UTILLS_H
