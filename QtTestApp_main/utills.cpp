#include "utills.h"

//-----NetworkIPInfo
Utills::NetworkIPInfo::NetworkIPInfo(){
    Clear();
}

Utills::NetworkIPInfo::NetworkIPInfo(bool is_dhcp,string ip, string gw, string dns){
    Set(is_dhcp, ip, gw, dns);
}

Utills::NetworkIPInfo::~NetworkIPInfo(){}


void Utills::NetworkIPInfo::Set(bool is_dhcp, string ip, string gw, string dns){
    _is_dhcp = is_dhcp;
    _ip = ip;
    _gateway = gw;
    _dns = dns;
}

void Utills::NetworkIPInfo::Clear(){
    _is_dhcp = true;
    _ip = NOINFORMATION;
    _gateway = NOINFORMATION;
    _dns = NOINFORMATION;

}

string Utills::NetworkIPInfo::ToLineString(){
    string ret_str = (_is_dhcp) ? "DHCP=ON" : "DHCP=OFF";
    return ret_str + ",IP=" + _ip + ",GATEWAY=" + _gateway + ",DNS=" + _dns;
}

void Utills::NetworkIPInfo::Show(bool with_header){

    string delim = "\t";

    if(with_header){
        vector<string> headers;
        // ヘッダーの整形
        headers.push_back("DHCP");
        headers.push_back("IP");
        headers.push_back("GATEWAY");
        headers.push_back("DNS");

        cout << Utills::MergeString(headers, delim) << endl;
    }

    vector<string> elements;
    if(this->_is_dhcp)
        elements.push_back("Yes");
    else
        elements.push_back("No");
    elements.push_back(this->_ip);
    elements.push_back(this->_gateway);
    elements.push_back(this->_dns);

    cout << Utills::MergeString(elements, delim) << endl;
    return;
}


//-----End of NetworkIPInfo Class


//-----NetoworkConnectInfo

Utills::NetworkConnectInfo::NetworkConnectInfo(){
      Clear();
}

Utills::NetworkConnectInfo::NetworkConnectInfo(string conname, string ifname, string net_type, bool is_dhcp, string ip, string gateway, string dns, string ssid){
    Set(conname, ifname, net_type, is_dhcp, ip, gateway, dns, ssid);
}

Utills::NetworkConnectInfo::NetworkConnectInfo(string conname, string ifname, string net_type, NetworkIPInfo net_ipinfo, string ssid){
    Set(conname, ifname, net_type, net_ipinfo._is_dhcp, net_ipinfo._ip, net_ipinfo._gateway, net_ipinfo._dns, ssid);
}


Utills::NetworkConnectInfo::~NetworkConnectInfo(){
}

void Utills::NetworkConnectInfo::Set(string conname, string net_type, string ifname, bool is_dhcp, string ip, string gateway, string dns, string ssid){
    _conname = conname;
    _ifname = ifname;
    _net_type = net_type;
    _is_dhcp = is_dhcp;
    _ip = ip;
    _gateway = gateway;
    _dns = dns;
    _ssid = ssid;
    _state = false;
}

void Utills::NetworkConnectInfo::Set(string conname, string net_type, string ifname, NetworkIPInfo net_ipinfo, string ssid){
    Set(conname, ifname, net_type, net_ipinfo._is_dhcp, net_ipinfo._ip, net_ipinfo._gateway, net_ipinfo._dns, ssid);
}


void Utills::NetworkConnectInfo::Clear(){
    _conname = NOINFORMATION;
    _ifname = NOINFORMATION;
    _net_type = NOINFORMATION;
    _is_dhcp = false;
    _ip = NOINFORMATION;
    _gateway = NOINFORMATION;
    _dns = NOINFORMATION;
    _ssid = NOINFORMATION;
    _state = false;
}

void Utills::NetworkConnectInfo::Show(bool with_header){

    string delim = "\t";

    if(with_header){
        vector<string> headers;
        // ヘッダーの整形
        headers.push_back("Name");
        headers.push_back("Device");
        headers.push_back("Type");
        headers.push_back("DHCP");
        headers.push_back("IP");
        headers.push_back("GATEWAY");
        headers.push_back("DNS");
        headers.push_back("SSID");
        headers.push_back("STATUS");

        cout << Utills::MergeString(headers, delim) << endl;
    }

    vector<string> elements;
    elements.push_back(this->_conname);
    elements.push_back(this->_ifname);
    elements.push_back(this->_net_type);
    if(this->_is_dhcp)
        elements.push_back("Yes");
    else
        elements.push_back("No");
    elements.push_back(this->_ip);
    elements.push_back(this->_gateway);
    elements.push_back(this->_dns);
    elements.push_back(this->_ssid);
    if(this->_state)
        elements.push_back("Connected");
    else
        elements.push_back("DisConnected");

    cout << Utills::MergeString(elements, delim) << endl;
    return;
}

//-----End of NetworkConnectInfo Class



int Utills::ShowMessageBox(const MessageState &msg_state, const QString &msg){


    QMessageBox msgBox;
    msgBox.setText(msg);

    switch(msg_state){
    case INFORMATION:
        msgBox.setWindowTitle("Information");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, "閉じる");
        msgBox.setIcon(QMessageBox::Icon::Information);
        break;
    case CONFIRMATION:
        msgBox.setWindowTitle("Confirmation");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Yes, "はい");
        msgBox.setButtonText(QMessageBox::Cancel, "いいえ");
        msgBox.setIcon(QMessageBox::Icon::Question);
        break;
    case WARNING:
        msgBox.setWindowTitle("Warning");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, "閉じる");
        msgBox.setIcon(QMessageBox::Icon::Warning);
        break;
    case CRITICAL:
        msgBox.setWindowTitle("Error");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes, "閉じる");
        msgBox.setIcon(QMessageBox::Icon::Critical);
        break;
    }

    int res = msgBox.exec();

    return res;
}


// ToString関数
string Utills::ToString(const NetworkType &net_type){
    switch(net_type){
    case NetworkType::ETHERNET:
        return "ethernet";
    case NetworkType::WIFI:
        return "wifi";
    default:
        return "unknown";
    }
}

string Utills::ToString(const NetworkState &net_state){

    switch(net_state){
    case NetworkState::CONNECTED:
        return "接続済み";
    case NetworkState::DISCONNECT:
        return "未接続";
    case NetworkState::UNAVAILABLE:
        return "利用不可";
    default:
        return "unknown";
    }

}


// 汎用関数群

string Utills::DoubleQuatationString(const string& src){
    return "\"" + src + "\"";
}

void Utills::SplitString(string src, const string& delim, vector<string>& result){

    //cout << "src : " << src << endl;
    //cout << "count : " << src.size() << endl;

    // 改行文字は消去する
    if(*(src.end() - 1) == '\n')
        src.erase(src.end() - 1);

    result.clear();

    string ::size_type pos = 0;
    while(pos != string::npos){

        string::size_type p = src.find(delim, pos);

        string tmp;
        if(p == string::npos){
            tmp = src.substr(pos);
            if(tmp.size() != 0) result.push_back(tmp);
            break;
        }
        else{
            tmp = src.substr(pos, p - pos);
            if(tmp.size() != 0) result.push_back(tmp);
        }

        pos = p + delim.size();
    }

    //Utills::ShowStringVector(result);

    return;
}

void Utills::SplitStringSpecial(string src, vector<string> &result, const char delim, const int repeat){

    // 改行文字は消去
    if(*(src.end() - 1) == '\n')
        src.erase(src.end() - 1);

    result.clear();

    string buff = "";
    int counter = 0;
    for(unsigned int i = 0; i < src.size(); i++){

        // delim以外の文字が来たとき
        if(src[i] != delim){

            // ここまでにdelimが連続してrepeat以上続いている
            if(counter >= repeat){
                result.push_back(buff);
                buff = "";
            }
            counter = 0;
            buff.push_back(src[i]);
        }

        //delimが来たとき
        else{
            counter++;
        }
    }

    // buffに文字が残っていれば追加
    if(buff.size() != 0) result.push_back(buff);

    return;
}

string Utills::MergeString(const vector<string>& src, const string& delim){

    string result = *src.begin();

    for(auto it = src.begin(); it != src.end(); it++){
        if(it == src.begin()) continue;
        result += delim + *it;
    }

    return result;
}

void Utills::ShowStringVector(const vector<string>& src, const bool& with_no){

    int count = 0;
    for(auto it = src.begin(); it != src.end(); it++){
        count++;
        if(with_no) cout << count << ".\t";
        cout << *it << endl;
    }
    return;
}


bool Utills::CheckStr_NoInfo(const string &src){
    return src == NOINFORMATION;
}
