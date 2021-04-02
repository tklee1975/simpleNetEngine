//
//  SNHostComponent.c
//  SimpleNet
//
//  Created by kenlee on 13/3/2021.
//

#include "SNHost.h"
#include "../SNSessionFactory.h"
#include "../SNSocket.h"
#include <iostream>
#include <simpleNet/CoreLib.h>


namespace simpleNet {


SNHost::SNHost() : SNNetBase()
{
    _state = SNHostStateIdle;
}
    
bool SNHost::bindPort(int port)
{
    _port = port;
    
//    if(_factory == NULL) {
//        std::cout << "SNHost: sessionFactory undefined\n";
//        return false;
//    }
    
    //
    // Get the socket reference
    initServerSocket(); //
    
    _serverSocket->setNonBlock(true);
    _serverSocket->setReuseAddress(true);
    // Create the TCP
    
    // Bind the port
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(_port);

    if(_serverSocket->bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return false;
    }
    
    if(_serverSocket->listen(10) == false) {
        std::cout << "Fail to listen\n";
        return false;
    }
    
    _state = SNHostStatetWaitForClient;
    
    return true;
}

void SNHost::initServerSocket()
{
    // ken: FIXME: Clear the previous connection
    _serverSocket = new SNSocket();
    _serverSocket->createTCP();
    //_serverSocket->setNonBlock(true);
}

void SNHost::initClientSocket()
{
    initSocket();
}
//
//SNSession *SNHost::getSession()
//{
//    return _session;
//}

bool SNHost::attemptAccept()
{
    if(_serverSocket == nullptr) {
        ERROR_LOG("attemptAccept: fail: socket is NULL");
        throw SNError("attemptAccept fail: socket not ready");
    }
    
    SNSocket newSock;
    SNSocketAcceptStatus status = _serverSocket->attempAccept(newSock);
    if(status == SNSocketAcceptStatus::Fail) {
        throw SNError("attemptAccept fail");
    }
    
    if(status == SNSocketAcceptStatus::Pending) {
        return false;
    }
    
    newSock.setNonBlock(true);
    if(createMainSession(std::move(newSock)) == false) {
        ERROR_LOG("Fail to create main session");
        return false;
    }
    _mainSession->setConnected(/* isHost */ true);
    
    //initClientSocket();
    //SNSocket sock = *_clientSocket;     // ken: HACK: is it okay?
//
//    SNSocketAcceptStatus status = _serverSocket->attempAccept(*_mainSocket);
//    if(status == SNSocketAcceptStatus::Fail) {
//        throw SNError("attemptAccept fail");
//    }
//
//    if(status == SNSocketAcceptStatus::Pending) {
//        return false;
//    }
//
//    // Create the Socket
//    _mainSocket->setNonBlock(true);
//    _session = _factory->create(_mainSocket);
//    _session->setConnected(/* isHost */ true);
//
    return true;
}

//
//bool SNHost::attemptAcceptOld()
//{
//    if(_serverSocket == NULL) {
//        ERROR_LOG("attemptAccept: fail: socket is NULL");
//        throw SNError("attemptAccept fail: socket not ready");
//    }
//    initClientSocket();
//    //SNSocket sock = *_clientSocket;     // ken: HACK: is it okay?
//
//    SNSocketAcceptStatus status = _serverSocket->attempAccept(*_mainSocket);
//    if(status == SNSocketAcceptStatus::Fail) {
//        throw SNError("attemptAccept fail");
//    }
//
//    if(status == SNSocketAcceptStatus::Pending) {
//        return false;
//    }
//
//    // Create the Socket
//    _mainSocket->setNonBlock(true);
//    _session = _factory->create(_mainSocket);
//    _session->setConnected(/* isHost */ true);
//
//    return true;
//}

//SNHostStatetIdle,
//SNHostStatetWaitForClient,            // after bindPort and before accept
//SNHostStatetConnected,                // after accepted
void SNHost::checkNetwork()
{
    if(SNHostStateIdle == _state) {
        // nothing to do
    } else if(SNHostStatetWaitForClient == _state) {
        checkNetworkWhenWaitClient();
    } else if(SNHostStatetConnected == _state) {
        checkNetworkWhenConnect();
    }
}

void SNHost::checkNetworkWhenWaitClient()
{
    bool isConnected = attemptAccept();
    if(isConnected) {
        _state = SNHostStatetConnected;
    }
}

void SNHost::checkNetworkWhenConnect()
{
    bool isConnected = checkIncomingData();
    if(isConnected == false) {
        
        _mainSession.release();
        _mainSession = nullptr;
        _state = SNHostStatetWaitForClient;
        LOG("Switching HostState");
    }
}

}
