#ifndef NETWORKSETTING_H
#define NETWORKSETTING_H

#include "utills.h"
#include "system.h"

class NetworkSetting{

public :
    System _sys;
    Utills::NetworkState _state; // 接続状態
    vector<Utills::NetworkConnectInfo> _nwci_list; // 接続情報リスト
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
    vector<string> GetSSIDList(); // SSIDのリストの取得

    // ネットワーク設定操作
    int ConnectionEdit(Utills::NetworkConnectInfo nwci, string pass); // 新しい接続情報の追加（Wifi用）
    int ConnectionDelete(int idx);
    int ConnectionReset(); // 初期化

    int TryConnect(int idx); // 指定したインデックスの接続情報で接続
    int TryDisConnect(); // 切断

};

#endif // NETWORKSETTING_H

/* *
 * ハードウェアはether,wifiともにひとつずつ仮定
 * いろんな接続ケースがあると仮定して、接続情報をユーザ指定の接続名で管理できるようにする。
 * ConnectionEditといいつつ、一旦接続情報を削除して再作成している。（同接続名の回避）
 * 一旦、同接続名の判定はせず、同じ接続名にした場合上書きされる仕様とする。
 * wifiのパスは情報としてプログラム内部では持たない。
 * ConnectionEditの際も再入力が必要な仕様とする。
 * */
