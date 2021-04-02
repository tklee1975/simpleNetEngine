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
#include "Type.h"
#include "Vector.h"

namespace simpleNet {




class SNString {
public:
    SNString();
    SNString(const char *str);
    
    const std::string &str() const;
    const char * c_str() const;
    
    void clear();
    void split(std::vector<SNString> &list, const char *delimiter);
    
    void set(const char *newStr);
    
    void append(const char *newStr);
    void append(const std::string &sStr);
    void append(SNVector<u8> &buffer);
    //template <class InputIterator>
    //void append(InputIterator first, const InputIterator last);
//    void append(std::vector::iterator<char *> first,
//                std::vector::iterator<char *> last);
//    
    
    void copyTo(std::vector<char> &outBuf);
    void copyTo(std::vector<u8> &outBuf);
    void appendTo(std::vector<u8> &outBuf);
    
    bool isEmpty() const;
    
    int toInt() const;
    
    bool startsWith(const char *prefix) const;
    
    void rtrim();
private:
    std::string _buf;
};

class SNStringUtil {
public:
    static void binToHex(SNString& result, SNVector<u8> data) {
        char str[5];
        
        result.clear();
        //result.append(data);
        for (int i=0; i<data.size(); i++) {
            sprintf(str, "%02x ", data[i]);
            
            result.append(str);
        }
//        result.clear();
//        appendBinToHex(result, data.data(), data.size());
        //result.clear();
    }

    
};


}
#endif /* String_h */
