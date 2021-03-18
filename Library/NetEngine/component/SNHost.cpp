//
//  SNHostComponent.c
//  SimpleNet
//
//  Created by kenlee on 13/3/2021.
//

#include "SNHost.h"
#include "SNSessionFactory.h"
#include "SNSocket.h"
#include <iostream>
#include <CoreLib.h>


namespace simpleNet {


SNHost::SNHost() : SNNetBase()
{
    _state = SNHostStateIdle;
}
    
bool SNHost::bindPort(int port)
{
    _port = port;
    
    if(_factory == NULL) {
        std::cout << "SNHost: sessionFactory undefined\n";
        return false;
    }
    
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
    if(_serverSocket == NULL) {
        log("ERROR: attemptAccept: fail: socket is NULL");
        throw SNError("attemptAccept fail: socket not ready");
    }
    initClientSocket();
    //SNSocket sock = *_clientSocket;     // ken: HACK: is it okay?
    
    SNSocketAcceptStatus status = _serverSocket->attempAccept(*_mainSocket);
    if(status == SNSocketAcceptFail) {
        throw SNError("attemptAccept fail");
    }
    
    if(status == SNSocketAcceptPending) {
        return false;
    }
    
    // Create the Socket
    _mainSocket->setNonBlock(true);
    _session = _factory->create(_mainSocket);
    _session->setConnected(/* isHost */ true);
    
    return true;
}

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
    checkIncomingData();
}
//
//void SNHost::queueToOutBuffer(SNString &str)
//{
//    if(str.str().size() == 0) {
//        return;
//    }
//
//    if(_session != NULL) {
//        _session->putBufferWithStr(str);
//    }
//}
//
//void SNHost::sendDataOut()
//{
//    if(_session == NULL) {
//        return;
//    }
//
//    _session->flushBuffer();
//}
//
//bool SNHost::checkIncomingData()
//{
//    // log("Checking Incoming data");
//    size_t nRead = 0;
//    if(_session->isConncting(nRead) == false) {  // check for data
//        return false;
//    }
//
//    // log("Checking receive data");
//    _session->receiveData();
//
//    return true;
//}
    
} // End of Namespace
