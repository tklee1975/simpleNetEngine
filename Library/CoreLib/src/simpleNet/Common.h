//
//  Common.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef Common_hpp
#define Common_hpp

#include <stdio.h>
#include <unistd.h> // sleep()
#include <exception>
#include <iostream>

namespace simpleNet {
//

// Common functions
inline void sleep(int sec) {
#ifdef _WIN32
    Sleep(sec * 1000);
#else
    ::sleep(sec);
#endif
}

//std::cout << "DUMP_HEX: " << tmp << "\n"; \
//// Helper Macro
#define SN_DUMP_HEX(v) \
    do{ \
        SNString tmp; \
        SNStringUtil::binToHex(tmp, v); \
        std::cout << "HEX: " << tmp.str() << "\n"; \
    } while(false) \
//------


// Common class

class SNError : public std::exception {
public:
    SNError(const char* msg = "") {
        std::cout << "ERROR: " << msg << "\n";
    }
};

}

#endif /* Common_hpp */
