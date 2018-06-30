#include <QCoreApplication>
#include "system.h"
#include "networksetting.h"

using namespace Utills;
using namespace Systems;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    //vector<string> tmp;
    //string src = "ABCD       tEFGH\tIJK";
    //Utills::SplitString(src, " ", tmp);

    /* *
     *Commandクラスのテスト
     * ・lsコマンドの送信
     * */
    cout << "----------Test Command Class---------" << endl;
    Command cmd;
    cmd.CMD_Test("ls -l");

    cout << "------------------------------------" << endl << endl;

    //return 0;

    /* *
     * NetworkManagerクラスのテスト
     * ・nmcliステータス確認
     * */
    cout << "----------Test NetworkManager Class---------" << endl;
    NetworkManager nm;
    cout << ">> Show Network Information" << endl;
    vector<Utills::NetworkConnectInfo> nwci_list;
    nm.UpdateInfo(nwci_list);
    for(auto it = nwci_list.begin();it != nwci_list.end(); it++){
        if(it == nwci_list.begin()){
            (*it).Show();
            continue;
        }
        (*it).Show(false);
    }
    cout << ">> Show SSID " << endl;
    vector<string> ssid_list;
    nm.GetSSIDList(ssid_list);
    Utills::ShowStringVector(ssid_list);
    cout << "------------------------------------" << endl << endl;

   /* *
    * NetworkSettingクラスのテスト
    * ・初期化テスト
    * ・Ethernet接続テスト
    * */
    cout << "----------Test NetworkSetting Class---------" << endl;
    NetworkSetting ns;

    // 初期状態の確認
    ns.ShowState();
    ns.ShowSSIDList();

    // 接続情報の削除
    ns.Reset();
    ns.ShowState(NetworkType::ETHERNET);

    // Ethernet接続操作テスト
    // 接続
    NetworkIPInfo net_ipinfo;
    bool is_dhcp = true;
    net_ipinfo.Set(is_dhcp);
    ns.Connect(NetworkType::ETHERNET, net_ipinfo);
    ns.ShowState(NetworkType::ETHERNET);
    // 切断
    ns.DisConnect(NetworkType::ETHERNET);
    ns.ShowState(NetworkType::ETHERNET);
    // 再接続
    ns.Connect(NetworkType::ETHERNET, net_ipinfo);
    ns.ShowState(NetworkType::ETHERNET);
    // 固定IP設定
    //string ip = "172.26.18.111", gateway = "172.26.18.254", dns = "150.61.227.17";
    //net_ipinfo.Set(false, ip, gateway, dns);
    //ns.Connect(NetworkType::ETHERNET, net_ipinfo);
    //ns.ShowState(NetworkType::ETHERNET);

    cout << "------------------------------------" << endl << endl;


    //return 0;
    return a.exec();
}

