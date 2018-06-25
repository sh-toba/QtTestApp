#ifndef SYSTEM_H
#define SYSTEM_H

#include "utills.h"

#define CMD_TIMEOUT_MSEC 100

#define DEVICE_ETHER string("eth0")
#define DEVICE_WIFI string("wlan0")
#define CMD_NETWORK_REBOOT string("sudo /etc/init.d/networking restart")
#define CMD_NETWORK_MANAGE string("nmcli")
#define CMD_STDOUT_DELIMITER ' '
#define CMD_STDOUT_DELIMITER_R 2

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
    int NMGetConnectionName(vector<tuple<string, bool>>& con_list);
    int NMGetConnectionInfo(const string conname, Utills::NetworkConnectInfo& nwci);

    string NMCordinateOpt(Utills::NetworkConnectInfo nwci);

public:

    System();
    ~System();

    // 接続情報を最新にする
    int NMUpdateInfo(vector<Utills::NetworkConnectInfo>& nwci_list);
    // SSIDを取得する
    int NMGetSSIDList(vector<string>& ssid_list);
    // 接続情報を編集する（追加 兼 編集）
    int NMConnectionEdit(Utills::NetworkConnectInfo nwci, string pass = NOINFORMATION);
    // 接続情報を削除する
    int NMConnectDelete(string conname);
    // 接続を確立する
    int NMConnectUp(string conname);
    // 接続を切断する
    int NMConnectDown(string conname);
    // デバッグ用 - 送信したコマンドの標準出力を受けとってコンソール表示
    int CMD_Test(string cmd_str);

};

#endif // SYSTEM_H

/* *
 * 備忘録メモ
 * 最悪nmcli以外で設定する場合も、Net
 * 今の所、nmcliのコマンドが失敗することに関しては寛容。フリーズすることはないため。
 * bufferからsuccesflyを抽出して各コマンドの成功を判定してもいいかもしれない
 * etherとwifiで全く同じオプションが使えるわけではないので、今の所接続プロセスを内部で分けている
 * こっちの内部での繰り返しを減らすため、コマンドの方でできる限り情報をフィルタする
 * */
