#ifndef SYSTEM_H
#define SYSTEM_H

#include "myutills.h"

#define MAX_BUFFER_LENGTH 1024
#define CMD_TIMEOUT_MSEC 100

#define DEVICE_ETHER "eth0"
#define DEVICE_WIFI "wlan0"
#define CMD_NETWORK_RESTART "sudo /etc/init.d/networking restart"
#define CMD_NETWORK_MANAGE "nmcli"

class System{

private:

    // 読み込んだコマンドの標準出力の一時保存（一行づつ）
    vector<string> _cmd_buff;

private:
    // コマンド送信
    int _send_cmd(string cmd_str);
    // バッファ開放(vectorのメモリリーク対策)
    void _clear_buff();

    int NMReboot();
    int NMConnectup();
    int NMConnectdown();

    string NMCordinateOpt(Utills::NetworkConnectInfo nwci);

public:

    System();
    ~System();

    // ネットワーク関連API
    int NMGetConnectInfo(Utills::NetworkState& state, vector<Utills::NetworkConnectInfo>& nwci_list, int& connected_idx);
    int NMGetSSIDList(vector<string>& ssid_list);
    int NMConnectionAdd(Utills::NetworkConnectInfo nwci);
    int NMConnectionAdd(Utills::NetworkConnectInfo nwci, string pass);
    int NMConnectionModify();

    // デバッグ用
    int WriteBuffConsole(string cmd_str);

};

#endif // SYSTEM_H
