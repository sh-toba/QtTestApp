#include "system.h"

System::System(){

}

System::~System(){

}

int System::_send_cmd(string cmd_str){

    cout << ">> $ " << cmd_str << endl;

    FILE *fp;
    char buff[MAX_BUFFER_LENGTH];
    if((fp = popen(cmd_str.c_str(), "r")) != NULL) {
        while(fgets(buff, sizeof(buff), fp) != NULL){
            string tmp_str = string(buff);
            //tmp_str.erase(--tmp_str.end());
            _cmd_buff.push_back(tmp_str);
        }
        pclose(fp);
        return 0;
    }
    return -1;

}

void System::_clear_buff(){
    vector<string>().swap(_cmd_buff);
    return;
}


int System::NMReboot(){

    int ret;

    ret = _send_cmd(CMD_NETWORK_REBOOT);
    _clear_buff();

    return ret;
}

int System::NMGetConnectionName(vector<tuple<string, bool>> &con_list){

    int ret;

    // 初期化
    con_list.clear();

    // コマンド整形・送信
    string cmd = string(CMD_NETWORK_MANAGE) + " -f NAME,DEVICE connection";
    ret = _send_cmd(cmd);

    // エラー処理？

    // 接続名、接続状態の取得
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){
        if(it == _cmd_buff.begin()) continue; // 一行目はヘッダ

        vector<string> split_str;
        Utills::SplitString(*it, CMD_STDOUT_DELIMITER, split_str);

        if(split_str.size() < 2) continue;

        // デバイス名が指定されていればアクティブ
        bool is_active = (split_str[1] == DEVICE_ETHER || split_str[1] == DEVICE_WIFI);
        con_list.push_back(make_tuple(split_str[0], is_active));
    }

    //バッファ初期化
    _clear_buff();

    return ret;
}

int System::NMGetConnectionInfo(const string conname, Utills::NetworkConnectInfo &nwci){

    int ret;
    string cmd;

    // 接続プロパティを調べる
    cmd = CMD_NETWORK_MANAGE + " -f connection,ipv4 connection show " + Utills::DoubleQuatationString(conname);
    ret = _send_cmd(cmd);

    vector<string> split_str;
    string con_type, property_name, value;
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        Utills::SplitString(*it, CMD_STDOUT_DELIMITER, split_str);
        property_name = split_str[0];
        value = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;

        if(property_name == "connection.id:")
            nwci.conname = value;
        else if (property_name == "connection.interface-name:")
            nwci.ifname = value;
        else if (property_name == "connection.type:")
            con_type = value;
        else if (property_name == "ipv4.method:"){
            if(value == "auto")
                nwci.is_dhcp = true;
            else if(value == "manual")
                nwci.is_dhcp = false;
        }
        else if (property_name == "ipv4.dns:")
            nwci.dns = value;
        else if (property_name == "ipv4.addresses:")
            nwci.ip = value;
        else if (property_name == "ipv4.gateway:")
            nwci.gateway = value;
    }

    _clear_buff();

    // Wifiの場合、SSIDを調べる
    if(nwci.ifname == DEVICE_WIFI){
        cmd = CMD_NETWORK_MANAGE + " -f " + con_type + ".ssid connection show " + conname;
        ret = _send_cmd(cmd);
        Utills::SplitString(_cmd_buff[0], CMD_STDOUT_DELIMITER, split_str);
        property_name = split_str[0];
        value = (split_str.size() < 2) ? split_str[1] : NOINFORMATION;
        nwci.ssid = value;
    }else{
        nwci.ssid = NOINFORMATION;
    }

    _clear_buff();

    return ret;
}

int System::NMConnectDelete(string conname){

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " delete " + conname);
    _clear_buff();

    return ret;
}

int System::NMConnectUp(string conname){

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " up " + conname);
    _clear_buff();

    return ret;
}

int System::NMConnectDown(string conname){

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " down " + conname);
    _clear_buff();

    return ret;
}

string System::NMCordinateOpt(Utills::NetworkConnectInfo nwci){

    // 接続名
    string opt = " con-name " + Utills::DoubleQuatationString(nwci.conname);

    // 接続デバイス名
    opt += " ifname " + nwci.ifname;

    // 接続タイプ
    if(nwci.ifname == DEVICE_ETHER){
        opt += " type ethernet";
    }
    else if(nwci.ifname == DEVICE_WIFI){
        opt += " type wifi";
        opt += " ssid " + nwci.ssid;
    }

    // 接続方法
    if(nwci.is_dhcp){
        opt += " ipv4.method auto";
        return opt;
    }else{
        // IPアドレス
        opt += " ipv4.addresses " + nwci.ip;
        // ゲートウェイ
        opt += " ipv4.gateway " + nwci.gateway;
        // DNS
        opt += " ipv4.dns " + nwci.dns;

        opt += " ipv4.method manual";
    }

    return opt;
}


int System::NMUpdateInfo(vector<Utills::NetworkConnectInfo> &nwci_list){

    int ret;
    string cmd;

    // 初期化
    nwci_list.clear();

    // 接続名と状態を取得する
    vector<tuple<string, bool>> con_list;
    ret = NMGetConnectionName(con_list);

    // エラー処理？？

    // 接続プロパティを調べていく
    for(auto it = con_list.begin(); it != con_list.end(); it++){

        Utills::NetworkConnectInfo nwci;

        ret = NMGetConnectionInfo(std::get<0>(*it), nwci);

        // エラー処理？？

        nwci.state = std::get<1>(*it);

        nwci_list.push_back(nwci);
    }

    return ret;
}

int System::NMGetSSIDList(vector<string> &ssid_list){

    int ret;

    // 初期化
    ssid_list.clear();

    // コマンド整形・送信
    string cmd = string(CMD_NETWORK_MANAGE) + " -f SSID d wifi list";
    ret = _send_cmd(cmd);

    // エラー処理？

    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){
        if(it == _cmd_buff.begin()) continue; // 一行目はヘッダ
        ssid_list.push_back(*it);
    }

    //バッファ初期化
    _clear_buff();

    return 0;
}

int System::NMConnectionEdit(Utills::NetworkConnectInfo nwci, string pass){

    int ret;

    // 指定した接続名がすでにあれば削除
    ret = NMConnectDelete(nwci.conname);

    // 接続
    string cmd = CMD_NETWORK_MANAGE;
    if(nwci.ifname == DEVICE_ETHER){
        ret = _send_cmd(cmd + " add" + NMCordinateOpt(nwci)); // 接続プロファイル作成
    }
    else if (nwci.ifname == DEVICE_WIFI){

        ret = _send_cmd(cmd + " device wifi connect " + nwci.ssid + " password " + pass + " name " + nwci.conname); // まず与えられたパスワードで接続を試みる.

        // 接続Failed判定および処理？？

        ret = _send_cmd(cmd + " modify " + nwci.conname + NMCordinateOpt(nwci));
    }

    ret = NMConnectUp(nwci.conname); // 接続確立

    ret = NMReboot(); // network再起動

    _clear_buff();

    return ret;
}


int System::CMD_Test(string cmd_str){

    _send_cmd(cmd_str);
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++)
        std::cout << *it << std::endl;
    _clear_buff();

    return 0;
}
