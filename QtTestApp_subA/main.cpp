#include <QCoreApplication>
#include "system.h"
#include "networksetting.h";

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    //vector<string> tmp;
    //string src = "ABCD       tEFGH\tIJK";
    //Utills::SplitString(src, " ", tmp);

    /* *
     *Systemクラスのテスト
     * ・lsコマンドの送信
     * */
    cout << "----------Test System Class---------" << endl;
    System sys;
    sys.CMD_Test("ls -l");

    cout << "------------------------------------" << endl << endl;

    /* *
     * Systemクラスのテスト
     * ・nmcliステータス確認
     * */
    cout << "----------Test System Class---------" << endl;
    cout << ">> Show Network Information" << endl;
    vector<Utills::NetworkConnectInfo> nwci_list;
    sys.NMUpdateInfo(nwci_list);
    for(auto it = nwci_list.begin();it != nwci_list.end(); it++){
        if(it == nwci_list.begin()){
            (*it).Show();
            continue;
        }
        (*it).Show(false);
    }
    cout << ">> Show SSID " << endl;
    vector<string> ssid_list;
    sys.NMGetSSIDList(ssid_list);
    Utills::ShowStringVector(ssid_list);
    cout << "------------------------------------" << endl << endl;

   /* *
    * NetworkSettingクラスのテスト
    * */
    cout << "----------Test NetworkSetting Class---------" << endl;
    NetworkSetting ns;
    ns.ConnectionReset(); // 接続情報のリセット
    ns.ShowMemberValues();

    cout << "<<<< Test Case Start >>>>" << endl;
    // 接続プロパティ
    Utills::NetworkConnectInfo nwci;
    string conname, ifname, ip, gateway, dns, ssid, pass;
    bool is_dhcp;

    ip = "192.168.10.111";
    gateway = "192.168.10.1";
    dns = "192.168.10.1";

    ssid = "hfuhiuhfiaudh";
    pass = "fjiofauh";

    cout << ">> Ethernet DHCP設定" << endl;
    conname = "MyEtherDHCP";
    ifname = DEVICE_ETHER;
    is_dhcp = true;
    nwci.Set(conname, ifname, is_dhcp);
    ns.ConnectionEdit(nwci);
    ns.ShowMemberValues();

    cout << ">> Ethernet 固定IP 設定" << endl;
    conname = "EtherFixIP";
    ifname = DEVICE_ETHER;
    is_dhcp = false;
    nwci.Set(conname, ifname, is_dhcp, ip, gateway, dns);
    ns.ConnectionEdit(nwci);
    ns.ShowMemberValues();

    cout << ">> Wifi DHCP設定" << endl;
    conname = "WifiDHCP";
    ifname = DEVICE_WIFI;
    is_dhcp = true;
    nwci.Set(conname, ifname, is_dhcp, NOINFORMATION, NOINFORMATION, NOINFORMATION, ssid);
    ns.ConnectionEdit(nwci, pass);
    ns.ShowMemberValues();

    cout << ">> Wifi 固定IP設定" << endl;
    conname = "WifiFixIP";
    ifname = DEVICE_WIFI;
    is_dhcp = false;
    nwci.Set(conname, ifname, is_dhcp, ip, gateway, dns, ssid);
    ns.ConnectionEdit(nwci, pass);
    ns.ShowMemberValues();

    cout << ">> 切り替え" << endl;
    ns.Connect(3);
    ns.ShowMemberValues();

    cout << ">> 削除" << endl;
    ns.ConnectionDelete(3);
    ns.ShowMemberValues();

    cout << ">> 切断" << endl;
    ns.DisConnect(1);
    ns.ShowMemberValues();

    cout << "------------------------------------" << endl << endl;


    //return 0;
    return a.exec();
}

