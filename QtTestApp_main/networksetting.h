#ifndef NETWORKSETTING_H
#define NETWORKSETTING_H

#include "utills.h"
#include "system.h"

using namespace Utills;
using namespace Systems;

class NetworkSetting{

private :
    NetworkManager _nm; // ネットワークマネージャクラス
    // デバイス名、接続状態、IPアドレス
    map<NetworkType, tuple<string, NetworkState, NetworkIPInfo>> _state; // 接続状態
    string _target_ssid; // 接続するSSID
    vector<string> _ssid_list; // SSIDリスト

private :
    int _UpdateState();
    int _ScanSSID();

public :
    NetworkSetting();
    ~NetworkSetting();

    // 初期化
    int Init();

    // API用Get関数
    NetworkState GetState(NetworkType net_type); // 接続状態
    NetworkIPInfo GetIPInfo(NetworkType net_type); // IPアドレス情報
    vector<string> GetSSIDList(); // SSIDのリスト取得

    // ネットワーク設定操作
    int Connect(NetworkType net_type, NetworkIPInfo net_ipinfo, string ssid=NOINFORMATION, string pass=NOINFORMATION);
    int DisConnect(NetworkType net_type); // 切断
    int Reset(); // 接続状態の初期化

    // デバッグ用
    void ShowState();
    void ShowState(NetworkType net_type);
    void ShowSSIDList();

};

#endif // NETWORKSETTING_H

/* *
 * （方針や仕様など）
 * NetworkManagerをGUIで使いやすい形に包括したつもりのクラス
 * 接続名称はUtillsで定義のデバイス名（インターフェース名）で固定にして設定する。
 * 　　・Systemクラスでは接続名単位で接続情報を設定できるが、ここではEther用, WiFi用で大別する。
 * インターフェースはether,wifiともにひとつずつと仮定。インターフェース名称も固定値で設定されているものとする。
 *
 * ConnectionEditといいつつ、一旦接続情報を削除して再作成している。（同接続名の回避）
 * 一旦、同接続名の判定はせず、同じ接続名にした場合上書きされる仕様とする。
 * wifiのパスは情報としてプログラム内部では持たない。
 * ConnectionEditの際も再入力が必要な仕様とする。
 * （エラー処理備忘録）
 * 電波の弱いWifiに繋ごうとして繋がらなかったとき。（電波強度でフィルタしてもよいかも）
 * その他の接続エラー
 * IPなどの入力規則はUtillsの方のクラスで
 * */
