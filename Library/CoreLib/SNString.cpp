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

