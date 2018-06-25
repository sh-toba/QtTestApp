#include "utills.h"

Utills::NetworkConnectInfo::NetworkConnectInfo(){

}

Utills::NetworkConnectInfo::NetworkConnectInfo(string conname, string ifname, bool is_dhcp, string ip, string gateway, string dns, string ssid){
    Set(conname, ifname, is_dhcp, ip, gateway, dns, ssid);
}

Utills::NetworkConnectInfo::~NetworkConnectInfo(){

}

void Utills::NetworkConnectInfo::Set(string conname, string ifname, bool is_dhcp, string ip, string gateway, string dns, string ssid){
    _conname = conname;
    _ifname = ifname;
    _is_dhcp = is_dhcp;
    _ip = ip;
    _gateway = gateway;
    _dns = dns;
    _ssid = ssid;
    _state = false;
}

void Utills::NetworkConnectInfo::Show(bool with_header){

    string delim = "\t";

    if(with_header){
        vector<string> headers;
        // ヘッダーの整形
        headers.push_back("Name");
        headers.push_back("Device");
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


string Utills::DoubleQuatationString(string src){
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
    for(int i = 0; i < src.size(); i++){

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

string Utills::MergeString(const vector<string> src, const string delim){

    string result = *src.begin();

    for(auto it = src.begin(); it != src.end(); it++){
        if(it == src.begin()) continue;
        result += delim + *it;
    }

    return result;
}

void Utills::ShowStringVector(const vector<string> src, bool with_no){

    int count = 0;
    for(auto it = src.begin(); it != src.end(); it++){
        count++;
        if(with_no) cout << count << ".\t";
        cout << *it << endl;
    }
    return;
}
