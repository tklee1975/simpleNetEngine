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


namespace simpleNet {


SNHost::SNHost()
{
    _state = SNHostStateIdle;
}
    
void SNHost::setSessionFactory(SNSessionFactory *factory)
{
    _factory = factory;
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
    // release current 
    if(_clientSocket) {
        delete _clientSocket;
        _clientSocket = NULL;
    }
    
    
    // ken: FIXME: Clear the previous connection
    _clientSocket = new SNSocket();
    //_serverSocket->createTCP();
    //_clientSocket->setNonBlock(true);
}

SNSession *SNHost::getSession()
{
    return _session;
}

bool SNHost::attemptAccept()
{
    if(_serverSocket == NULL) {
        log("ERROR: attemptAccept: fail: socket is NULL");
        throw SNError("attemptAccept fail: socket not ready");
    }
    initClientSocket();
    //SNSocket sock = *_clientSocket;     // ken: HACK: is it okay?
    
    SNSocketAcceptStatus status = _serverSocket->attempAccept(*_clientSocket);
    if(status == SNSocketAcceptFail) {
        throw SNError("attemptAccept fail");
    }
    
    if(status == SNSocketAcceptPending) {
        return false;
    }
    
    // Create the Socket
    _clientSocket->setNonBlock(true);
    _session = _factory->create(_clientSocket);
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

bool SNHost::checkIncomingData()
{
    // log("Checking Incoming data");
    size_t nRead = 0;
    if(_session->isConncting(nRead) == false) {  // check for data
        return false;
    }
    
    // log("Checking receive data");
    _session->receiveData();
    
    return true;
}
    
} // End of Namespace