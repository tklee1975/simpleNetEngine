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
 
    const std::string &SNString::str() const
    {
        return _buf;
    }

    const char * SNString::c_str() const
    {
        return _buf.c_str();
    }

    bool SNString::isEmpty() const 
    {
        return _buf.empty();
    }

    int SNString::toInt() const
    {
        try {
            return std::stoi(_buf);
        } catch(...) {
            return 0;
        }
    }

    bool SNString::startsWith(const char *prefix) const
    {
        int len = strlen(prefix);
        return strncmp(_buf.c_str(), prefix, len) == 0;
    }

    void SNString::rtrim()
    {
        // https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
        // ken: optimise later
        _buf.erase(std::find_if(_buf.rbegin(), _buf.rend(), [](unsigned char ch) {
                        return !std::isspace(ch);
                    }).base(), _buf.end());
    }

    void SNString::split(std::vector<SNString> &list, const char *delimiter)
    {
        std::string s = std::string(_buf);
        size_t pos = 0;
        std::string token;
        
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            list.emplace_back(token.c_str());
            s.erase(0, pos + strlen(delimiter));
        }
        
        list.emplace_back(s.c_str());
        //return list;
    }

    void SNString::set(const char *newStr){
        _buf.clear();
        _buf.append(newStr);
    }
    
//    template <class InputIterator>
//    void SNString::append(InputIterator first, InputIterator last)
//    {
//    //    _buf.append(first, last);
//    }

    void SNString::append(const std::string &sStr)
    {
        _buf.append(sStr);
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

    void SNString::copyTo(std::vector<u8> &outBuf)
    {
        // Reference:
        //  https://stackoverflow.com/questions/8247793/converting-stdstring-to-stdvectorchar
        outBuf.clear();
        std::copy(_buf.begin(), _buf.end(), std::back_inserter(outBuf));

    }
    
    void SNString::appendTo(std::vector<u8> &outBuf)
    {
    // Reference:
    //  https://stackoverflow.com/questions/8247793/converting-stdstring-to-stdvectorchar
        std::copy(_buf.begin(), _buf.end(), std::back_inserter(outBuf));
    }
}


