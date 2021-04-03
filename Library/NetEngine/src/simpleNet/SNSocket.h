//
//  SNSocket.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef SNSocket_hpp
#define SNSocket_hpp



#ifdef _WIN32
    #include <Winsock2.h> // must include before windows.h
    #include <Windows.h>
    #include <conio.h>
    #include <ws2tcpip.h> // getaddrinfo
    #pragma comment(lib, "Ws2_32.lib")
#else
    #include <unistd.h> // sleep()
    #include <arpa/inet.h> // htons
    #include <sys/socket.h>
    #include <netdb.h> // struct addrinfo
    #include <sys/ioctl.h>
#endif

#include <vector>
#include <simpleNet/CoreLib.h>

#pragma once

namespace simpleNet {

enum class SNSocketAcceptStatus {
    Success,
    Pending,
    Fail,
};

class SNSocketAddr {
public:
    SNSocketAddr();

    void setPort(uint16_t port);
    uint16_t port() const;

    void setIPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

    struct sockaddr _addr;
};

class SNSocket : NonCopyable {
public:
    
    // Data
#ifdef _WIN32
    typedef int socklen_t;
#else
    typedef int SOCKET;
    const SOCKET INVALID_SOCKET = -1;
#endif

    SNSocket();
    SNSocket(SNSocket &&other); // move constructor

    
    // Constructor & Destructor
    ~SNSocket() {
        close();
    }

    static void platformInit();
    void createUDP();
    void createTCP();
    void close();

    bool bind(const SNSocketAddr& addr);
    bool connect(const SNSocketAddr& addr);
    bool listen(int backLog);
    //int send(const SNSocketAddr& addr, const char* data, size_t dataSize);    // no use??
    int recv(std::vector<u8> & buf, size_t bytesToRecv);
    bool accept(SNSocket &acceptedSocket);
    SNSocketAcceptStatus attempAccept(SNSocket &acceptedSocket);
    
    int send(const u8* data, size_t dataSize);
    int send(const char* data, size_t dataSize);
    size_t availableBytesToRead();
    int getSockFd();
    
    // Options
    void setNonBlock(bool isNonBlack);
    void setReuseAddress(bool enableReuse);
    
    void mockConnect();
    void printInfo();
    
private:
    SOCKET _sock = INVALID_SOCKET;
    bool _enableReuseAddress;   // reuse address and port!
    
    void enableReuseAddress(const SNSocketAddr& addr);
};


}
#endif /* SNSocket_hpp */
