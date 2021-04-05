//
//  Common.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef Common_hpp
#define Common_hpp


#if _WIN32

#define _CRT_SECURE_NO_WARNINGS     1
#define NOMINMAX    1

#include <WinSock2.h>  // WinSock2 must befor window.h to avoid winsock1
#include <ws2tcpip.h>  // struct sockaddr_in6  
#pragma comment(lib, "Ws2_32.lib")

#include <Windows.h>


#else 
#include <unistd.h> // sleep()


#endif 

#include <stdio.h>
#include <exception>
#include <iostream>

// Case Function 
inline int my_strcasecmp(const char* a, const char* b) {
#if _MSC_VER
    return _stricmp(a, b);
#else 
    return strcasecmp(a, b);
#endif 
}


namespace simpleNet {

// Enum
template<class T> inline constexpr typename std::underlying_type<T>::type enumInt(T value) {
    return static_cast<typename std::underlying_type<T>::type>(value);
}

template<class T> inline constexpr typename std::underlying_type<T>::type &enumIntRef(T& value) {
    return *reinterpret_cast<typename std::underlying_type<T>::type*>(&value);
}

template<class T> inline constexpr typename std::underlying_type<T>::type const & enumIntRef(const T& value) { return *reinterpret_cast<const typename std::underlying_type<T>::type*>(&value); }

template<class T> inline bool constexpr enumHas        (const T& a, const T& b) { return static_cast<T>(enumInt(a) & enumInt(b)) != static_cast<T>(0); }


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
