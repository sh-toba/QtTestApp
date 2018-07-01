#include "networksetting.h"

NetworkSetting::NetworkSetting(){
    //Init();
}

NetworkSetting::~NetworkSetting(){

}


int NetworkSetting::_UpdateState(){

    int ret;

    NetworkType net_type;
    string ifname;
    NetworkState tmp_state;
    NetworkConnectInfo tmp_nwci;

    // 更新処理
    for(int i=NetworkType::ETHERNET; i <= NetworkType::WIFI; i++){
        net_type = static_cast<NetworkType>(i);
        ifname = get<0>(_state[net_type]);
        // 情報取得
        ret = _nm.GetDeviceState(ifname, tmp_state);
        ret = _nm.GetConnectionInfo(ifname, tmp_nwci);
        // 更新
        get<1>(_state[net_type]) = tmp_state;
        get<2>(_state[net_type]).Set(tmp_nwci._is_dhcp, tmp_nwci._ip, tmp_nwci._gateway, tmp_nwci._dns);
        //if(net_type == NetworkType::WIFI) _target_ssid = tmp_nwci._ssid; // SSID
    }

    return ret;
}


int NetworkSetting::_ScanSSID(){
    int ret = _nm.GetSSIDList(_ssid_list);
    return ret;
}


int NetworkSetting::Init(){

    LOG_DEBUG("%s","");

    int ret;

    // 初期化
    _state.clear();
    _target_ssid = NOINFORMATION;
    _ssid_list.clear();

    string ifname;
    NetworkType net_type;

    // ETHERNET初期状態
    net_type = NetworkType::ETHERNET;
    ret = _nm.GetDeviceName(net_type, ifname);
        // エラー処理？ - デバイスが見つからない場合
    _state.insert(make_pair(net_type, make_tuple(ifname, NetworkState::DISCONNECT, NetworkIPInfo())));

    // WIFI初期状態
    net_type = NetworkType::WIFI;
    ret = _nm.GetDeviceName(net_type, ifname);
        // エラー処理？ - デバイスが見つからない場合
    _state.insert(make_pair(net_type, make_tuple(ifname, NetworkState::DISCONNECT, NetworkIPInfo())));

    // デバイス名ハードコーディングの場合
    //_state.insert(make_pair(NetworkType::ETHERNET, make_tuple(DEVICE_ETHER, NetworkState::DISCONNECT, NetworkIPInfo())));
    //_state.insert(make_pair(NetworkType::WIFI, make_tuple(DEVICE_WIFI, NetworkState::DISCONNECT, NetworkIPInfo())));

    ret = _UpdateState();
    ret = _ScanSSID();

    LOG_DEBUG("%s","Initialization Complete");

    return ret;
}


NetworkState NetworkSetting::GetState(const NetworkType& net_type){

    LOG_DEBUG("%s",Utills::ToString(net_type).c_str());

    return get<1>(_state[net_type]);
}

NetworkIPInfo NetworkSetting::GetIPInfo(const NetworkType& net_type){

    LOG_DEBUG("%s",Utills::ToString(net_type).c_str());

    return get<2>(_state[net_type]);
}

vector<string> NetworkSetting::GetSSIDList(){

    LOG_DEBUG("%s","");

    _ScanSSID(); // 再スキャンする
    return _ssid_list;
}

string NetworkSetting::GetTargetSSID(){
    return _target_ssid;
}


int NetworkSetting::Connect(const NetworkType& net_type, const NetworkIPInfo& net_ipinfo, const string& ssid, const string& pass){

    LOG_DEBUG("%s", "");
    //LOG_DEBUG("nettype:%s|ipinfo:%s|ssid:%s", Utills::ToString(net_type).c_str(), (net_ipinfo.ToLineString()).c_str(), ssid.c_str());

    int ret;

    string ifname = get<0>(_state[net_type]);

    string net_type_str;
    if(net_type == NetworkType::ETHERNET)
        net_type_str = "ethernet";
    else if(net_type == NetworkType::WIFI)
        net_type_str = "wifi";
    else{
        return -1;
    }

    // 接続情報をSyetemクラスで扱える形に形成
    NetworkConnectInfo nwci;
    if(net_type == NetworkType::ETHERNET){
        nwci.Set(ifname, ifname, net_type_str, net_ipinfo);
        ret = _nm.ConnectionEdit(nwci);
    }
    else if(net_type == NetworkType::WIFI){
        nwci.Set(ifname, ifname, net_type_str, net_ipinfo, ssid);
        _target_ssid = ssid;
        ret = _nm.ConnectionEdit(nwci, pass);
    }
    else{
        // エラー処理? - API使用ミス
        return -1;
    }

    // retエラー判定?

    // 接続状態の更新
    ret = _UpdateState();

    LOG_DEBUG("%s", "Connect Complete");

    return ret;
}

int NetworkSetting::DisConnect(const NetworkType& net_type){

    LOG_DEBUG("%s", Utills::ToString(net_type).c_str());

    int ret;

    string ifname = get<0>(_state[net_type]);
    ret = _nm.ConnectDown(ifname);

    // retエラー判定?

    // 接続状態の更新
    ret = _UpdateState();

    LOG_DEBUG("%s", "DisConnect Complete");

    return ret;
}

int NetworkSetting::Reset(){

    LOG_DEBUG("%s","");

    int ret;

    NetworkType net_type;
    string ifname;

    for(int i=NetworkType::ETHERNET; i <= NetworkType::WIFI; i++){

        net_type = static_cast<NetworkType>(i);
        ifname = get<0>(_state[net_type]);

        ret = _nm.ConnectDelete(ifname);

        // retエラー判定?
    }

    // 接続状態の更新
    ret = Init();

    LOG_DEBUG("%s", "Reset Complete");

    return ret;
}


void NetworkSetting::ShowState(){

    cout << "=========NetworkSetting::ShowState===========" << endl;
    for(int i=NetworkType::ETHERNET; i <= NetworkType::WIFI; i++){
        NetworkType net_type = static_cast<NetworkType>(i);
        cout << "NetworkType : " << net_type << endl;
        cout << "Device : " << get<0>(_state[net_type]) << endl;
        cout << "State : " << get<1>(_state[net_type]) << endl;
        cout << "IPv4 Information : " << endl;
        get<2>(_state[net_type]).Show();
        //if(net_type == NetworkType::WIFI) cout << "SSID : " << _target_ssid << endl;
    }
    cout << endl;

    return;
}

void NetworkSetting::ShowState(const NetworkType& net_type){

    cout << "=========NetworkSetting::ShowState===========" << endl;
    cout << "NetworkType : " << net_type << endl;
    cout << "Device : " << get<0>(_state[net_type]) << endl;
    cout << "State : " << get<1>(_state[net_type]) << endl;
    cout << "IPv4 Information : " << endl;
    get<2>(_state[net_type]).Show();
    cout << endl;

    return;
}

void NetworkSetting::ShowSSIDList(){

    cout << "=========NetworkSetting::ShowSSIDList===========" << endl;
    Utills::ShowStringVector(_ssid_list);
    cout << endl;

    return;

}
