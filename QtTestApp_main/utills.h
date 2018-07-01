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
#include <time.h>

using namespace std;

#define MAX_BUFFER_LENGTH 1024
#define NOINFORMATION string("--")

#define ENUM_STRING(var)

// #define DEVICE_ETHER string("eth0") // 未使用
// #define DEVICE_WIFI string("wlan0") // 未使用

#define CMD_TIMEOUT_MSEC 100
#define CMD_STDOUT_DELIMITER ' '
#define CMD_STDOUT_DELIMITER_R 2

namespace Utills {


// 固定IP接続用の設定情報(IPv4) - NetwarkSettingクラス以上で扱う
class NetworkIPInfo{

public:
    bool _is_dhcp; // DHCP
    string _ip; // IPアドレス(IPv4)
    string _gateway; // ゲートウェイ(IPv4)
    string _dns; // DHSサーバー(IPv4)

    NetworkIPInfo();
    NetworkIPInfo(bool is_dhcp, string ip=NOINFORMATION, string gw=NOINFORMATION, string dns=NOINFORMATION);
    ~NetworkIPInfo();

    void Set(bool is_dhcp, string ip=NOINFORMATION, string gw=NOINFORMATION, string dns=NOINFORMATION);
    void Clear();

    // デバッグ用
    string ToLineString();
    void Show(bool with_header=true);
};

// ネットワーク接続で必要となる情報 - Systemクラスで扱う
class NetworkConnectInfo{

public :
    string _conname; // 接続名
    string _ifname; // インターフェース名
    string _net_type; // ネットワークタイプ
    bool _is_dhcp; // DHCP
    string _ip; // IPアドレス(IPv4)
    string _gateway; // ゲートウェイ(IPv4)
    string _dns; // DHSサーバー(IPv4)
    string _ssid; // SSID(WiFiのみ必要)
    bool _state; // 接続状態

    NetworkConnectInfo();
    NetworkConnectInfo(string conname, string ifname, string net_type, bool is_dhcp, string ip = NOINFORMATION, string gateway = NOINFORMATION, string dns = NOINFORMATION, string ssid = NOINFORMATION);
    NetworkConnectInfo(string conname, string ifname, string net_type, NetworkIPInfo net_ipinfo, string ssid=NOINFORMATION);
    ~NetworkConnectInfo();

    void Set(string conname, string ifname, string net_type, bool is_dhcp, string ip = NOINFORMATION, string gateway = NOINFORMATION, string dns = NOINFORMATION, string ssid = NOINFORMATION);
    void Set(string conname, string ifname, string net_type, NetworkIPInfo net_ipinfo, string ssid=NOINFORMATION);

    void Clear();

    // デバッグ用
    void Show(bool with_header=true);
};

// 接続タイプ
enum NetworkType{
    ETHERNET,
    WIFI,
    MISC,
};

// 接続状態
enum NetworkState{
    DISCONNECT,
    CONNECTED,
    UNAVAILABLE,
};

/* *ToString関数
 * Network関連で上記を上手くまとめられると良かった
 * */

string ToString(const NetworkType& net_type);
string ToString(const NetworkState& net_state);

/* * std::string系 汎用関数群
 *
 *
 * */

// 文字列を二重引用符で囲んで返す
string DoubleQuatationString(const string& src);
// 文字列分割
void SplitString(string src, const string& delim, vector<string>& result);
// 文字列分割 - 「指定数以上delimが続く」条件で分割する。delimもすべて消去される。
void SplitStringSpecial(string src,  vector<string>& result, const char delim = ' ', const int repeat = 1);
// 文字列合成
string MergeString(const vector<string>& src, const string& delim);
// vector<string>のリストの表示
void ShowStringVector(const vector<string>& src, const bool& with_no=true);


/* * GUI入力規則のチェック関連
 *
 * */

bool CheckStr_IP(string ip); // 未実装
bool CheckStr_GateWay(string gateway); // 未実装
bool CheckStr_DNS(string dns); // 未実装
bool CheckStr_NoInfo(const string& src);

}

#endif // UTILLS_H
