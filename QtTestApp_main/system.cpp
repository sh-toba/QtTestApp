#include "system.h"

System::System(){

}

System::~System(){

}

int System::_send_cmd(string cmd_str){

    FILE *fp;
    char buff[MAX_BUFFER_LENGTH];
    if((fp = popen(cmd_str.c_str(), "r")) != NULL) {
        while(fgets(buff, sizeof(buff), fp) != NULL){
            string tmp_str = string(buff);
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
    _send_cmd(string(CMD_NETWORK_RESTART));
    _clear_buff();
    return 0;
}


string System::NMCordinateOpt(Utills::NetworkConnectInfo nwci){

    // 接続名
    string opt = " con-name " + Utills::DoubleQuatationString(nwci.name);

    // 接続タイプ
    opt += " type " + nwci.type;

    // デバイス名
    if(nwci.type == "ethernet")
        opt += " ifname " + string(DEVICE_ETHER);
    else if(nwci.type == "wifi"){
        opt += " ifname " + string(DEVICE_WIFI);
        opt += " ssid " + nwci.ssid;
        opt += " pass"; // ------------------------ここまで
    }

    // DHCP
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
    }

    return opt;
}

int System::NMGetConnectInfo(Utills::NetworkState &state, vector<Utills::NetworkConnectInfo> &nwci_list, int &connected_idx){
    return 0;
}

int System::NMGetSSIDList(vector<string> &ssid_list){
    return 0;
}

int System::WriteBuffConsole(string cmd_str){

    _send_cmd(cmd_str);
    for(auto it = _cmd_buff.begin(); it != _cmd_buff.end(); it++)
        std::cout << *it << std::endl;
    _clear_buff();

    return 0;
}
