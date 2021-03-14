//
//  String.c
//  SimpleNet
//
//  Created by kenlee on 7/3/2021.
//

#include "SNString.h"

namespace simpleNet {

    SNString::SNString()
        :_buf("")
    {}

    SNString::SNString(const char * str)
        :_buf(str)
    {}
 
    std::string SNString::str() {
        return _buf;
    }

    const char * SNString::c_str()
    {
        return _buf.c_str();
    }

    bool SNString::isEmpty()
    {
        return _buf.empty();
    }

    int SNString::toInt()
    {
        try {
            return std::stoi(_buf);
        } catch(...) {
            return 0;
        }
    }

    bool SNString::startsWith(const char *prefix)
    {
        return _buf.rfind(prefix) == 0;
    }

    void SNString::rtrim()
    {
        // https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
        _buf.erase(
                   std::find_if(_buf.rbegin(), _buf.rend(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }).base(), _buf.end());
    }

    std::vector<SNString> SNString::split(const char *delimiter)
    {
        std::vector<SNString> list;
            
        std::string s = std::string(_buf);
        size_t pos = 0;
        std::string token;
        
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            list.push_back(SNString(token.c_str()));
            s.erase(0, pos + strlen(delimiter));
        }
        
        list.push_back(SNString(s.c_str()));
        return list;
    }

    void SNString::set(const char *newStr){
        _buf.clear();
        _buf.append(newStr);
    }
    
    void SNString::append(const char *newStr)
    {
        _buf.append(newStr);
    }
    
    void SNString::copyTo(std::vector<char> &outBuf) {
        // Reference:
        //  https://stackoverflow.com/questions/8247793/converting-stdstring-to-stdvectorchar
        outBuf.clear();
        std::copy(_buf.begin(), _buf.end(), std::back_inserter(outBuf));

    }
    
}

