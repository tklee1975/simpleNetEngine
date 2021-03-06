//
//  SNSocket.cpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#include "SNSocket.h"
#include <iostream>
#include <unistd.h>
#include <exception>
#include <CoreLib.h>

#define BACKLOG 10

namespace simpleNet {

/**
 SNSocketAddr
 */
SNSocketAddr::SNSocketAddr()
{
	memset(&_addr, 0, sizeof(_addr));
}

void SNSocketAddr::setPort(uint16_t port)
{
    *reinterpret_cast<uint16_t*>(_addr.sa_data) = htons(port);
}

uint16_t SNSocketAddr::port() const
{
    return ntohs(*reinterpret_cast<const uint16_t*>(_addr.sa_data));
}

void SNSocketAddr::setIPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    _addr.sa_family = AF_INET;
    _addr.sa_data[2] = a;
    _addr.sa_data[3] = b;
    _addr.sa_data[4] = c;
    _addr.sa_data[5] = d;
}


/**
 Socket
 */
class SNSocketInit {
public:
#ifdef _WIN32
    SNSocketInit() {
        WSADATA data;
        if (0 != WSAStartup(MAKEWORD(2,2), &data)) {
            std::cout << "fail to start up Winsocket\n";
            return;
            //throw std::exception("WSAStartup");
        }
    }

    ~SNSocketInit() {
        WSACleanup();
    }

    static void init() {
        static MySocketInit s;
    }
#else
    static void init() {
    }
#endif
};

/**
 SNSocket
 */
void SNSocket::close()
{
    if (_sock != INVALID_SOCKET)
    {
        #ifdef _WIN32
            closesocket(_sock);
        #else
            ::close(_sock);
        #endif
        _sock = INVALID_SOCKET;
    }
}

void SNSocket::createTCP()
{
    close();

//    MySocketInit::init();
    _sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == INVALID_SOCKET) {
        // throw std::exception("createTCP");
        std::cout << "fail to connect socket\n";
        return;
    }
    std::cout << "socket okay. sock=" << _sock << "\n";
}

bool SNSocket::bind(const SNSocketAddr& addr)
{
    int ret = ::bind(_sock, &addr._addr, sizeof(addr._addr));
    if (ret != 0) {
        //throw MyError("bind");
        std::cout << "fail to bind socket\n";
        return false;
    }

    std::cout << "Bind to port: " <<  addr.port() << "\n";
    return true;
}


void SNSocket::recv(std::vector<char> & buf, size_t bytesToRecv)
{
    buf.clear();
    if (bytesToRecv > INT_MAX) {
        std::cout << "recv bytesToRecv is too big\n";
        //throw MyError("recv bytesToRecv is too big");
        return;
    }
    
    buf.resize(bytesToRecv);

    SNSocketAddr addr;
    socklen_t addrLen = sizeof(addr._addr);
    int ret = ::recvfrom(_sock, buf.data(),
                        (int)bytesToRecv, 0, &addr._addr, &addrLen);
    if (ret < 0) {
        std::cout << "recv error: " << ret << "\n";
        //throw MyError("recv");
        return;
    }
    std::cout << ret << " byte received\n";
}


bool SNSocket::listen(int backLog)
{
    int ret = ::listen(_sock, BACKLOG);
    if (ret != 0) {
        //throw MyError("bind");
        std::cout << "fail to bind socket\n";
        return false;
    }

    std::cout << "Start Listening\n";
    simpleNet::log("Waiting for incoming data");
    
    return true;
}


bool SNSocket::accept(SNSocket &acceptedSocket)
{
    acceptedSocket.close();

    auto c = ::accept(_sock, nullptr, nullptr);
    if (c == INVALID_SOCKET) {
        return false;
    }

    printf("accept\n");
    acceptedSocket._sock = c;
    return true;
}


void SNSocket::send(const char* data, size_t dataSize)
{
    if (dataSize > INT_MAX) {
        std::cout << "Send dataSize too big\n";
        return;
    }

    int ret = ::send(_sock, data, (int)dataSize, 0);
    if (ret < 0) {
        std::cout << "Fail to send " << ret << "\n";
        return;
    }
    
    return;
}




}
