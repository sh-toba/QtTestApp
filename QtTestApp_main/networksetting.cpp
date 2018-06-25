#include "networksetting.h"

NetworkSetting::NetworkSetting(){
    Init();
}

NetworkSetting::~NetworkSetting(){

}


int NetworkSetting::_UpdateInfo(){

    // 接続情報更新
    int ret = _sys.NMUpdateInfo(_nwci_list);

    // ステータス更新
    bool tmp = false;
    for(auto it = _nwci_list.begin(); it != _nwci_list.end(); it++)
       tmp |= (*it)._state;

    _state = (tmp) ? Utills::NetworkState::CONNECT : Utills::NetworkState::DISCONNECT;

    return ret;
}

int NetworkSetting::_ScanSSID(){
    int ret = _sys.NMGetSSIDList(_ssid_list);
    return ret;
}


void NetworkSetting::Init(){

    int ret;

    ret = _UpdateInfo();
    ret = _ScanSSID();

    return;
}

Utills::NetworkState NetworkSetting::GetState(){
    return _state;
}

vector<Utills::NetworkConnectInfo> NetworkSetting::GetNWCIList(){
    return _nwci_list;
}

vector<string> NetworkSetting::GetSSIDList(){
    _ScanSSID(); // 再スキャンする
    return _ssid_list;
}


int NetworkSetting::ConnectionEdit(Utills::NetworkConnectInfo nwci, string pass){

    int ret;

    ret = _sys.NMConnectionEdit(nwci, pass);

    ret = _UpdateInfo();

    return ret;
}

int NetworkSetting::Connect(int idx){

    int ret;

    ret = _sys.NMConnectUp(_nwci_list[idx]._conname);

    ret = _UpdateInfo();

    return ret;
}

int NetworkSetting::DisConnect(int idx){

    int ret;

    ret = _sys.NMConnectDown(_nwci_list[idx]._conname);

    ret = _UpdateInfo();

    return ret;
}

int NetworkSetting::ConnectionDelete(int idx){

    int ret;

    if(_nwci_list[idx]._state)
        ret = _sys.NMConnectDown(_nwci_list[idx]._conname);

    ret = _sys.NMConnectDelete(_nwci_list[idx]._conname);

    ret = _UpdateInfo();

    return ret;
}

int NetworkSetting::ConnectionReset(){

    int ret;

    for(auto it = _nwci_list.begin(); it != _nwci_list.end(); it++){

        if((*it)._state)
            ret = _sys.NMConnectDown((*it)._conname);

        ret = _sys.NMConnectDelete((*it)._conname);
    }

    ret = _UpdateInfo();

    return ret;

}


void NetworkSetting::ShowMemberValues(){

    cout << "----- STATUS -----" << endl;
    string msg;
    switch(_state){
    case Utills::NetworkState::CONNECT:
        msg = "Connected";
        break;
    case Utills::NetworkState::DISCONNECT:
        msg = "DisConnected";
        break;
    }
    cout << msg << endl;

    cout << "----- Network Connection Information -----" << endl;
    for(auto it = _nwci_list.begin();it != _nwci_list.end(); it++){
        if(it == _nwci_list.begin()){
            (*it).Show();
            continue;
        }
        (*it).Show(false);
    }
    cout << endl;

    cout << "----- SSID List -----" << endl;
    Utills::ShowStringVector(_ssid_list);

    return;

}
