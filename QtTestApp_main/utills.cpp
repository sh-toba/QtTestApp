#include "utills.h"

void Utills::NetworkConnectInfo::Show(bool with_header){

    string delim = "\t";

    if(with_header){
        vector<string> headers;
        // ヘッダーの整形
        headers.push_back("Name");
        headers.push_back("STATUS");
        headers.push_back("Device");
        headers.push_back("DHCP");
        headers.push_back("IP");
        headers.push_back("GATEWAY");
        headers.push_back("DNS");
        headers.push_back("SSID");

        cout << Utills::MergeString(headers, delim) << endl;
    }

    vector<string> elements;
    elements.push_back(this->conname);
    if(this->state)
        elements.push_back("Connected");
    else
        elements.push_back("DisConnected");
    elements.push_back(this->ifname);
    if(this->is_dhcp)
        elements.push_back("Yes");
    else
        elements.push_back("No");
    elements.push_back(this->ip);
    elements.push_back(this->gateway);
    elements.push_back(this->dns);
    elements.push_back(this->ssid);

    cout << Utills::MergeString(elements, delim) << endl;
    return;
}

string Utills::DoubleQuatationString(string src){
    return "\"" + src + "\"";
}

void Utills::SplitString(const string& src, const string& delim, vector<string>& result){

    //cout << "src : " << src << endl;
    //cout << "count : " << src.size() << endl;

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
