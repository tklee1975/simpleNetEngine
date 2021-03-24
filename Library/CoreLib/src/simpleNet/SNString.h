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

namespace simpleNet {


class SNString {
public:
    SNString();
    SNString(const char *str);
    
    std::string str();
    const char * c_str();
    
    std::vector<SNString> split(const char *delimiter);
    
    void set(const char *newStr);
    void append(const char *newStr);
    void copyTo(std::vector<char> &outBuf);
    void appendTo(std::vector<char> &outBuf);
    
    bool isEmpty();
    
    int toInt();
    
    bool startsWith(const char *prefix);
    
    void rtrim();
private:
    std::string _buf;
};


}
#endif /* String_h */
