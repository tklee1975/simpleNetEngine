//
//  String.h
//  SimpleNet
//
//  Created by kenlee on 7/3/2021.
//

#ifndef String_h
#define String_h

#include <stdio.h>
#include <vector>
#include <string>
#include <simpleNet/CoreLib.h>

namespace simpleNet {


class SNString {
public:
    SNString();
    SNString(const char *str);
    
    const std::string &str() const;
    const char * c_str() const;
    
    void split(std::vector<SNString> &list, const char *delimiter);
    
    void set(const char *newStr);
    void append(const char *newStr);
    void copyTo(std::vector<char> &outBuf);
    void copyTo(std::vector<uint8_t> &outBuf);
    void appendTo(std::vector<char> &outBuf);
    
    bool isEmpty() const;
    
    int toInt() const;
    
    bool startsWith(const char *prefix) const;
    
    void rtrim();
private:
    std::string _buf;
};


}
#endif /* String_h */
