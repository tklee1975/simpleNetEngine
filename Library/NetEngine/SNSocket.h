//
//  SNSocket.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef SNSocket_hpp
#define SNSocket_hpp

#include <arpa/inet.h> // htons
#include <sys/socket.h>
#include <vector>

#pragma once

namespace simpleNet {

class SNSocketAddr {
public:
    SNSocketAddr();

    void setPort(uint16_t port);
    uint16_t port() const;

    void setIPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

    struct sockaddr _addr;
};

class SNSocket {
public:
    
    // Data
#ifdef _WIN32
    typedef int socklen_t;
#else
    typedef int SOCKET;
    const SOCKET INVALID_SOCKET = -1;
#endif

    // Constructor & Destructor
    ~SNSocket() {
        close();
        
    }

    void createUDP();
    void createTCP();
    void close();

    bool bind(const SNSocketAddr& addr);
    bool listen(int backLog);
    void send(const SNSocketAddr& addr, const char* data, size_t dataSize);
    void recv(std::vector<char> & buf, size_t bytesToRecv);
    bool accept(SNSocket &acceptedSocket);
    void send(const char* data, size_t dataSize);
    
private:
    SOCKET _sock = INVALID_SOCKET;
};


}
#endif /* SNSocket_hpp */
