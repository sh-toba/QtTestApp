#ifndef NetworkManager_H
#define NetworkManager_H

#include "utills.h"
#include "logger.h"

#define CMD_NETWORK_REBOOT string("sudo /etc/init.d/networking restart")
#define CMD_NETWORK_MANAGE string("nmcli")

using namespace Utills;


namespace Systems {

///
/// \brief The Command class
///
class Command{

protected:
    // 読み込んだコマンドの標準出力の一時保存（一行づつ）
    vector<string> _cmd_buff;

protected:
    // コマンド送信
    int _send_cmd(string cmd_str);
    // バッファ開放
    void _clear_buff();

public:

    Command();
    ~Command();

    // デバッグ用 - 送信したコマンドの標準出力を受けとって再表示
    int CMD_Test(string cmd_str);
};


///
/// \brief The NetworkManager class
///


class NetworkManager : Command{

private:
    // ネットワーク再起動 （実はいらないかもしれない）
    int Reboot();

    // 接続名のリストと接続状態をペアで返す
    int GetConnectionName(vector<tuple<string, bool>>& con_list);

    // 接続名の存在確認
    bool _ConnectionNameExist(); // 未実装。

    // network-managerのオプション形成
    string CordinateOpt(string mode, NetworkConnectInfo nwci);

public:

    NetworkManager();
    ~NetworkManager();

    // 指定したタイプのデバイス名を返す
    int GetDeviceName(const NetworkType net_type, string& ifname);
    // 指定したデバイス名の接続状態を返す
    int GetDeviceState(const string ifname, NetworkState& state);
    // 指定した接続名の情報を返す
    int GetConnectionInfo(const string conname, NetworkConnectInfo& nwci);
    // SSIDを取得する
    int GetSSIDList(vector<string>& ssid_list);
    // 接続情報を最新にする
    // 上位で接続名レベルで管理したい場合にのみ使用（現在は使っていない）
    int UpdateInfo(vector<NetworkConnectInfo>& nwci_list);

    // 接続情報を編集する（追加 兼 編集）
    int ConnectionEdit(NetworkConnectInfo nwci, string pass = NOINFORMATION);
    // 接続情報を削除する
    int ConnectDelete(string conname);
    // 接続を確立する
    int ConnectUp(string conname);
    // 接続を切断する
    int ConnectDown(string conname);

};

} // NAMESPACE NetworkManager

#endif // NetworkManager_H

/* *
 * 備忘録メモ
 * あまり意味ないですが、Systemsの名前空間でくくっています。
 * 最初はSystemクラスとして包括してましたが、ネットワーク設定のクラス部分が想像以上に膨らんできたので、
 * 基本的なCommandから派生して目的別にクラスを作っていくようにしました。
 * 最悪cli以外で設定する場合も、Net
 * 今の所、cliのコマンドが失敗することに関しては寛容。フリーズすることはないため。
 * bufferからsuccesflyを抽出して各コマンドの成功を判定してもいいかもしれない
 * etherとwifiで全く同じオプションが使えるわけではないので、今の所接続プロセスを内部で分けている
 * こっちの内部での繰り返しを減らすため、コマンドの方でできる限り情報をフィルタする
 * */
