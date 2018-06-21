#ifndef NETWORKSETTING_H
#define NETWORKSETTING_H

#include "myutills.h"
#include "system.h"

class NetworkSetting{

public :
    System _sys;
    Utills::NetworkState _state; // 接続状態
    vector<Utills::NetworkConnectInfo> _nwci_list; // 接続情報リスト
    int _connected_idx; // 上記のリスト中での接続中の番号
    vector<string> _ssid_list; // SSIDリスト

private:
    bool _CheckStr_IP(string ip);
    bool _CheckStr_GateWay(string gateway);
    bool _CheckStr_DNS(string dns);

    bool _CheckExist_ConName(string name);

    int _LoadConnectInfo();
    int _ScanSSID();

public :
    NetworkSetting();
    ~NetworkSetting();

    // API用Get関数
    Utills::NetworkState GetState(); // 接続状態
    vector<Utills::NetworkConnectInfo> GetNWCIList(); // 接続情報のリストを取得
    int GetConnectedIdx(); // 接続中の接続情報のインデックス
    vector<string> GetSSIDList(); // SSIDのリストの取得

    // ネットワーク設定操作
    int ConnectionAdd(Utills::NetworkConnectInfo nwci); // 新しい接続情報の追加（Ether用）
    int ConnectionAdd(Utills::NetworkConnectInfo nwci, string pass); // 新しい接続情報の追加（Wifi用）
    int ConnectionEdit(Utills::NetworkConnectInfo nwci); // 接続情報の変更
    int ConnectionDelete(int idx);
    int ConnectionReset(); // 初期化

    int TryConnect(int idx); // 指定したインデックスの接続情報で接続
    int TryDisConnect(); // 切断

};

#endif // NETWORKSETTING_H
