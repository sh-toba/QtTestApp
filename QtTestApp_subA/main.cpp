#include <QCoreApplication>
#include "system.h"

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
    cout << "------------------------------------" << endl;

    /* *
     * Systemクラスのテスト
     * ・nmcliステータス確認
     * ・nmcli設定
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
    cout << "------------------------------------" << endl;

   /* *
    * NetworkSettingクラスのテスト
    *
    *
    * */

    //return 0;
    return a.exec();
}

