#include "system.h"

// Command Class

Systems::Command::Command(){}
Systems::Command::~Command(){}

// protected method
int Systems::Command::_send_cmd(const string& cmd_str){

    //cout << ">> $ " << cmd_str << endl;
    LOG_INFO("%s", cmd_str.c_str());

    FILE *fp;
    char buff[MAX_BUFFER_LENGTH];
    if((fp = popen(cmd_str.c_str(), "r")) != NULL) {
        while(fgets(buff, sizeof(buff), fp) != NULL){
            string tmp_str = string(buff);
            //tmp_str.erase(--tmp_str.end());
            _cmd_buff.push_back(tmp_str);
        }
        pclose(fp);

        LOG_INFO("%s", "aaa");

        return 0;
    }

    LOG_INFO("%s", "bbb");

    return -1;

}

void Systems::Command::_clear_buff(){
    vector<string>().swap(_cmd_buff);
    return;
}

// For Debug
int Systems::Command::CMD_Test(const string& cmd_str){

    _send_cmd(cmd_str);
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++)
        std::cout << *it << std::endl;
    _clear_buff();

    return 0;
}

// End of Command Class


// NetworkManager Class (inheritance of Command Class)

Systems::NetworkManager::NetworkManager(){}
Systems::NetworkManager::~NetworkManager(){}

// private method
int Systems::NetworkManager::Reboot(){

    int ret;

    ret = _send_cmd(CMD_NETWORK_REBOOT);
    _clear_buff();

    return ret;
}

int Systems::NetworkManager::GetConnectionName(vector<tuple<string, bool>> &con_list){

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
        Utills::SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);

        if(split_str.size() < 2) continue;

        // デバイス名が指定されていればアクティブ
        bool is_active = (split_str[1] != NOINFORMATION);
        con_list.push_back(make_tuple(split_str[0], is_active));
    }

    //バッファ初期化
    _clear_buff();

    return ret;
}

string Systems::NetworkManager::CordinateOpt(const string& mode, const NetworkConnectInfo& nwci){

    string opt = "";

    // add or modify
    if(mode != "add" && mode != "modify") return opt;

    // 接続名
    opt = " con-name " + Utills::DoubleQuatationString(nwci._conname);

    // 接続デバイス名
    opt += " ifname " + nwci._ifname;

    // 接続タイプ(add専用)
    if(mode == "add")
        opt += " type " + nwci._net_type;

    // SSID(Wifi専用)
    if(nwci._net_type == "wifi")
        opt += " ssid " + nwci._ssid;

    // 接続方法
    if(nwci._is_dhcp){
        opt += " ipv4.method auto";
        return opt;
    }else{
        // IPアドレス
        opt += " ipv4.addresses " + nwci._ip;
        // ゲートウェイ
        opt += " ipv4.gateway " + nwci._gateway;
        // DNS
        opt += " ipv4.dns " + nwci._dns;

        opt += " ipv4.method manual";
    }

    return opt;
}

// public method
int Systems::NetworkManager::GetDeviceName(const NetworkType& net_type, string &ifname){

    LOG_INFO("%s", Utills::ToString(net_type).c_str());

    int ret;

    // 初期化
    ifname = NOINFORMATION;

    // 標準出力に対応した名前に変換
    string net_type_str = Utills::ToString(net_type);

    // コマンド整形・送信
    string cmd = string(CMD_NETWORK_MANAGE) + " -f DEVICE,TYPE device";
    ret = _send_cmd(cmd);

    // 情報を抜き出す
    vector<string> split_str;
    string tmp_name, tmp_type;
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        if(it == _cmd_buff.begin()) continue; // 一行目はヘッダ

        SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);
        tmp_name = split_str[0];
        tmp_type = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;

        // 対応したタイプのデバイス名が見つかれば格納してリターン
        if(tmp_type == net_type_str){

            ifname = tmp_name;

            _clear_buff();
            return ret;
        }

    }

    _clear_buff();

    //LOG_INFO("return ifname:%s", ifname.c_str());

    return ret;
}

int Systems::NetworkManager::GetDeviceState(const string& ifname, NetworkState &state){

    LOG_INFO("%s", ifname.c_str());

    int ret;

    // 初期化
    state = NetworkState::UNAVAILABLE;

    // コマンド整形・送信
    string cmd = string(CMD_NETWORK_MANAGE) + " -f DEVICE,STATE device";
    ret = _send_cmd(cmd);

    // 情報を抜き出す
    vector<string> split_str;
    string tmp_name, tmp_state;
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        if(it == _cmd_buff.begin()) continue; // 一行目はヘッダ

        SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);
        tmp_name = split_str[0];
        tmp_state = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;

        // 指定されたデバイス名が見つかれば状態を格納してリターン
        if(tmp_name == ifname){

            // 標準出力内容を内部ステータスに変換
            if(tmp_state == "connected")
                state = NetworkState::CONNECTED;
            else if(tmp_state == "disconnected")
                state = NetworkState::DISCONNECT;
            else if(tmp_state == "unavailable")
                state = NetworkState::UNAVAILABLE;

            _clear_buff();
            return ret;
        }

    }

    _clear_buff();
    return ret;
}

int Systems::NetworkManager::GetConnectionInfo(const string& conname, NetworkConnectInfo &nwci){

    LOG_INFO("%s", conname.c_str());

    int ret;
    string cmd;

    // 初期化
    nwci.Clear();

    // 接続プロパティを調べる
    cmd = CMD_NETWORK_MANAGE + " -f connection,ipv4 connection show " + Utills::DoubleQuatationString(conname);
    ret = _send_cmd(cmd);

    vector<string> split_str;
    string con_type, property_name, value;

    // 設定されている情報を調べる
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);
        property_name = split_str[0];
        value = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;

        if(property_name == "connection.id:")
            nwci._conname = value;
        else if (property_name == "connection.interface-name:")
            nwci._ifname = value;
        else if (property_name == "connection.type:"){
            con_type = value;
            if(con_type.find("ethernet") != string::npos) nwci._net_type = "ethernet";
            else if(con_type.find("wifi") != string::npos) nwci._net_type = "wifi";
            else nwci._net_type = NOINFORMATION;
        }
        else if (property_name == "ipv4.method:"){
            if(value == "auto")
                nwci._is_dhcp = true;
            else if(value == "manual")
                nwci._is_dhcp = false;
        }
        else if (property_name == "ipv4.dns:")
            nwci._dns = value;
        else if (property_name == "ipv4.addresses:")
            nwci._ip = value;
        else if (property_name == "ipv4.gateway:")
            nwci._gateway = value;
    }
    _clear_buff();

    // 接続状態を調べる。 （接続中の場合、IP4プロパティが存在する）
    cmd = CMD_NETWORK_MANAGE + " -f IP4 connection show " + Utills::DoubleQuatationString(conname);
    ret = _send_cmd(cmd);
    nwci._state = (_cmd_buff.size() != 0) ? true : false;
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);
        property_name = split_str[0];
        value = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;

        if(property_name == "IP4.ADDRESS[1]:")
            nwci._ip = value;
        else if (property_name == "IP4.GATEWAY:")
            nwci._gateway = value;
        else if (property_name == "IP4.DNS[1]:")
            nwci._dns = value;
    }
    _clear_buff();

    // Wifiの場合、SSIDを調べる
    if(nwci._net_type == "wifi"){
        cmd = CMD_NETWORK_MANAGE + " -f " + con_type + ".ssid connection show " + conname;
        ret = _send_cmd(cmd);
        Utills::SplitStringSpecial(_cmd_buff[0], split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);
        property_name = split_str[0];
        value = (split_str.size() == 2) ? split_str[1] : NOINFORMATION;
        nwci._ssid = value;
    }else{
        nwci._ssid = NOINFORMATION;
    }
    _clear_buff();

    return ret;
}

int Systems::NetworkManager::GetSSIDList(vector<string> &ssid_list){

    LOG_INFO("%s", "");

    int ret;

    // 初期化
    ssid_list.clear();

    // コマンド整形・送信
    string cmd = string(CMD_NETWORK_MANAGE) + " -f SSID d wifi list";
    ret = _send_cmd(cmd);

    // エラー処理？

    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++){

        if(it == _cmd_buff.begin()) continue; // 一行目はヘッダ

        vector<string> split_str;
        Utills::SplitStringSpecial(*it, split_str, CMD_STDOUT_DELIMITER, CMD_STDOUT_DELIMITER_R);

        if(split_str.size() != 1) continue;

        ssid_list.push_back(split_str[0]);
    }

    //バッファ初期化
    _clear_buff();

    return ret;
}

int Systems::NetworkManager::UpdateInfo(vector<NetworkConnectInfo> &nwci_list){

    LOG_INFO("%s", "");

    int ret;
    string cmd;

    // 初期化
    nwci_list.clear();

    // 接続名と状態を取得する
    vector<tuple<string, bool>> con_list;
    ret = GetConnectionName(con_list);

    // エラー処理？？

    // 接続プロパティを調べていく
    for(auto it = con_list.begin(); it != con_list.end(); it++){

        Utills::NetworkConnectInfo nwci;

        ret = GetConnectionInfo(std::get<0>(*it), nwci);

        // エラー処理？？

        nwci._state = std::get<1>(*it);

        nwci_list.push_back(nwci);
    }

    return ret;
}


int Systems::NetworkManager::ConnectionEdit(const NetworkConnectInfo& nwci, const string& pass){

    LOG_INFO("%s", "");

    int ret;

    // 指定した接続名がすでにあれば削除
    ret = ConnectDelete(nwci._conname);

    // 接続
    string cmd = CMD_NETWORK_MANAGE;
    if(nwci._net_type == "ethernet"){
        ret = _send_cmd(cmd + " connection add " + CordinateOpt("add", nwci)); // 接続プロファイル作成
    }
    else if (nwci._net_type == "wifi"){

        ret = _send_cmd(cmd + " device wifi connect " + nwci._ssid + " password " + pass + " name " + nwci._conname); // まず与えられたパスワードで接続を試みる.

        // 接続Failed判定および処理？？

        ret = _send_cmd(cmd + " connection modify " + nwci._conname + CordinateOpt("modify", nwci));
    }else{
        // エラー処理？
        return -1;
    }

    ret = ConnectUp(nwci._conname); // 接続確立

    ret = Reboot(); // network再起動

    _clear_buff();

    return ret;
}

int Systems::NetworkManager::ConnectDelete(const string& conname){

    LOG_INFO("%s", conname.c_str());

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " connection delete " + conname);
    _clear_buff();

    return ret;
}

int Systems::NetworkManager::ConnectUp(const string& conname){

    LOG_INFO("%s", conname.c_str());

    LOG_INFO("%s", conname.c_str());

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " connection up " + conname);
    _clear_buff();

    return ret;
}

int Systems::NetworkManager::ConnectDown(const string& conname){

    LOG_INFO("%s", conname.c_str());

    int ret;

    ret = _send_cmd(CMD_NETWORK_MANAGE + " connection down " + conname);
    _clear_buff();

    return ret;
}

// End of Network Manager Class
