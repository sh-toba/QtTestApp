#include "myutills.h"

string Utills::DoubleQuatationString(string src){
    return "\"" + src + "\"";
}

void Utills::SplitString(const string& src, const string& delim, vector<string>& result){

    result.clear();

    string ::size_type pos = 0;

    while(pos != string::npos){

        string::size_type p = src.find(delim, pos);

        if(p == string::npos){
            result.push_back(src.substr(pos));
            break;
        }
        else{
            result.push_back(src.substr(pos, p - pos));
        }

        pos = p + delim.size();
    }
    return;
}
