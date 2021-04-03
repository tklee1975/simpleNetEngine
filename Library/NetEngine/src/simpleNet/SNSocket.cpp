//
//  SNSocket.cpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//


#include "SNSocket.h"
#include <iostream>
#include <exception>
#include <simpleNet/CoreLib.h>
#include <fcntl.h> /* Added for the nonblocking socket */

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
        static SNSocketInit s;
    }
#else
    static void init() {
    }
#endif
};


SNSocket::SNSocket()
{
    _enableReuseAddress = false;
}

SNSocket::SNSocket(SNSocket &&other)
: _sock(other._sock)
{
    // Copy
    std::cout << "Move Constructor is called\n";
    other._sock = INVALID_SOCKET;
}

void SNSocket::platformInit() {
    SNSocketInit::init();
}

int SNSocket::getSockFd()
{
    return _sock;
}

void SNSocket::setReuseAddress(bool enableReuse)
{
    _enableReuseAddress = enableReuse;
}

void SNSocket::setNonBlock(bool nonBlock)
{
#ifdef _WIN32
    u_long v = nonBlock ? 1 : 0;
    ::ioctlsocket(_sock, FIONBIO, &v);
#else 
    int flags;
    flags = ::fcntl(_sock, F_GETFL, 0);   // F_GETFL =  Get the file access mode
                                        //           and the file status flags;
    //assert(flags != -1);
    if (nonBlock) {
        ::fcntl(_sock, F_SETFL, flags | O_NONBLOCK);     // Set the mode to nonBlock
        //::fcntl(_sock, F_SETFL, flags |);     // Set the mode to nonBlock
    }
    else {
        fcntl(_sock, F_SETFL, flags & ~O_NONBLOCK);    // unset nonBlocking flag

    }

#endif 
}

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
        std::cout << "Socket is closed\n";
    }
}

void SNSocket::createTCP()
{
    platformInit();

    
    close();

    _sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == INVALID_SOCKET) {
        // throw std::exception("createTCP");
        std::cout << "fail to connect socket\n";
        return;
    }
    // std::cout << "socket okay. sock=" << _sock << "\n";
}


int SNSocket::getSockError() 
{
#if _WIN32
    int ret = WSAGetLastError();
#else
    int ret = errno;
#endif
    return ret;
}

void SNSocket::enableReuseAddress(const SNSocketAddr& addr)
{
    if(_sock <= INVALID_SOCKET) {
        std::cout << "enableReuseAddress: socket not ready\n";
        return;
    }

#if !_WIN32
    setsockopt(_sock, SOL_SOCKET, SO_REUSEPORT,
        reinterpret_cast<const char*>(&addr._addr),
        static_cast<int>(sizeof(addr._addr)));
#endif  
    setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR,
        reinterpret_cast<const char*>(&addr._addr),
        static_cast<int>(sizeof(addr._addr)));

    std::cout << "DEBUG: enableReuseAddress: option is set\n";
}

bool SNSocket::bind(const SNSocketAddr& addr)
{
    if(_enableReuseAddress) {
        enableReuseAddress(addr);
    }
    
    int ret = ::bind(_sock, &addr._addr, sizeof(addr._addr));
    if (ret != 0) {
        //throw MyError("bind");
        std::cout << "fail to bind socket\n";
        return false;
    }

    std::cout << "Bind to port: " <<  addr.port() << "\n";
    return true;
}



bool SNSocket::listen(int backLog)
{
    int ret = ::listen(_sock, BACKLOG);
    if (ret != 0) {
        //throw MyError("bind");
        
        std::cout << "fail to bind socket\n";
        return false;
    }

    LOG("Waiting for incoming data");
    
    return true;
}


bool SNSocket::connect(const SNSocketAddr& addr)
{
    int ret = ::connect(_sock, &addr._addr, sizeof(addr._addr));
    if (ret < 0) {

#ifdef _WIN32
        int e = WSAGetLastError();
        if (e == WSAEWOULDBLOCK) // connect in non-blocking mode
            return false;
#else
        int e = errno;
        if (e == EINPROGRESS) // connect in non-blocking mode
            return false;
#endif

        ERROR_LOG("connect: fail to connect: %d; error=%d", ret, errno);
        throw SNError("connect");
    }
    ERROR_LOG("connect: Socket connected");
    
    return true;
}

SNSocketAcceptStatus SNSocket::attempAccept(SNSocket &acceptedSocket)
{
    acceptedSocket.close();

    // https://jameshfisher.com/2017/04/05/set_socket_nonblocking/
    int value = ::accept(_sock, nullptr, nullptr);

//#ifdef _WIN32
//    int e = WSAGetLastError();
//    if (e == WSAEWOULDBLOCK) // connect in non-blocking mode
//        return false;
//#else
//    int e = errno;
//    if (e == EINPROGRESS) // connect in non-blocking mode
//        return false;
//#endif
//

    if (value == -1) {
        int err = getSockError();
#if _WIN32
        if (err == WSAEWOULDBLOCK){
            return SNSocketAcceptStatus::Pending;
        }
        return SNSocketAcceptStatus::Fail;
#else 
        if (err == EWOULDBLOCK) {
            return SNSocketAcceptStatus::Pending;
        }
        return SNSocketAcceptStatus::Fail;

#endif 
    }
    
    acceptedSocket._sock = value;
    
    return SNSocketAcceptStatus::Success;
//    if (c == INVALID_SOCKET) {
//        return false;
//    }
//
//    // printf("accept\n");
//    acceptedSocket._sock = c;
//    return true;
}


bool SNSocket::accept(SNSocket &acceptedSocket)
{
    acceptedSocket.close();

    auto c = ::accept(_sock, nullptr, nullptr);
    if (c == INVALID_SOCKET) {
        return false;
    }

    // printf("accept\n");
    acceptedSocket._sock = c;
    return true;
}


int SNSocket::send(const char* data, size_t dataSize)
{
    return send(reinterpret_cast<const u8*>(data), dataSize);
}


int SNSocket::send(const u8* data, size_t dataSize)
{
    if (dataSize > INT_MAX) {
        std::cout << "Send dataSize too big\n";
        return -1;
    }

    int ret = ::send(_sock, reinterpret_cast<const char *>(data),
                        static_cast<int>(dataSize), 0);
    if (ret < 0) {
        std::cout << "Fail to send " << ret << "\n";
        return -1;
    }
    //std::cout << "DataSize: " << dataSize << "\n";
    
    return ret; 
}


size_t SNSocket::availableBytesToRead()
{
#ifdef _WIN32
    u_long n = 0;

    if (0 != ::ioctlsocket(_sock, FIONREAD, &n)) {
        throw SNError("availableBytesToRead");
    }
    
    return static_cast<size_t>(n);
#else
    int n = 0;
    
    // io control: FIONREAD,
    // returns the number of data bytesin the location pointed
    int result = ::ioctl(_sock, FIONREAD, &n);
    if (0 != result) {
        ERROR_LOG("ERROR: availableBytesToRead: result is %d errno=%d", result, errno);
        throw SNError("availableBytesToRead");
    }

    return static_cast<size_t>(n);
#endif
    return 0;
}



int SNSocket::recv(std::vector<u8> & buf, size_t bytesToRecv)
{
    buf.clear();
    
    if (bytesToRecv > INT_MAX) {
        throw SNError("recv: bytesToRecv is too big");
    }
    
    buf.resize(bytesToRecv);

    int ret = ::recv(_sock, reinterpret_cast<char *>(buf.data()), 
                        static_cast<int>(bytesToRecv), 0);
    if (ret < 0) {
        throw SNError("recv: fail to recv");
    }

    return ret;
}

void SNSocket::mockConnect()
{
    _sock = 100;
}

void SNSocket::printInfo()
{
    std::cout << "info: " << _sock << "\n";
}
}
