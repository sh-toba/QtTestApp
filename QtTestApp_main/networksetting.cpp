#include "networksetting.h"

NetworkSetting::NetworkSetting(){

    _LoadConnectInfo();
    //_state = Utills::NetworkState::DISCONNECTED;
    //_nwci_list = vector<Utills::NetworkConnectInfo>();
    //_connected_idx = -1;
    //_ssid_list = vector<string>();

    return;
}

NetworkSetting::~NetworkSetting(){

}

int NetworkSetting::_LoadConnectInfo(){
    int ret = _sys.NMGetConnectInfo(_state, _nwci_list, _connected_idx);
    return ret;
}

int NetworkSetting::_ScanSSID(){
    int ret = _sys.NMGetSSIDList(_ssid_list);
    return ret;
}

Utills::NetworkState NetworkSetting::GetState(){
    return _state;
}

vector<Utills::NetworkConnectInfo> NetworkSetting::GetNWCIList(){
    return _nwci_list;
}

int NetworkSetting::GetConnectedIdx(){
    return _connected_idx;
}

vector<string> NetworkSetting::GetSSIDList(){
    return _ssid_list;
}
