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
    void append(const char *newStr);
    void copyTo(std::vector<char> &outBuf);
    
private:
    std::string _buf;
};


}
#endif /* String_h */
