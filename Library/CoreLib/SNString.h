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
    
    
    void set(const char *newStr);
    void append(const char *newStr);
    void copyTo(std::vector<char> &outBuf);
    bool isEmpty();
private:
    std::string _buf;
};


}
#endif /* String_h */
