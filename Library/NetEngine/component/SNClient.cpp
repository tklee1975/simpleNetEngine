//
//  SNClient.c
//  NetEngine
//
//  Created by kenlee on 13/3/2021.
//

#include "SNClient.h"
#include "SNSessionFactory.h"
#include "SNSocket.h"
#include <iostream>


namespace simpleNet {


SNClient::SNClient()
{
    _state = SNClientStateIdle;
}
    
void SNClient::setSessionFactory(SNSessionFactory *factory)
{
    _factory = factory;
}

bool SNClient::connectServer(const SNSocketAddr &addr)
{
    if(_factory == NULL) {
        std::cout << "SNClient: sessionFactory undefined\n";
        return false;
    }
    
    //
    // Get the socket reference
    initClientSocket(); //
    
    
    _clientSocket->connect(addr);
    
    _clientSocket->setNonBlock(true);
    // Create the TCP
    
    
    
    _session = _factory->create(_clientSocket);
    _session->setConnected(/* isHost */ false);
    
    _state = SNClientStatetConnected;
    
    return true;
}

SNSession *SNClient::getSession()
{
    return _session;
}


void SNClient::initClientSocket()
{
    // release current
    if(_clientSocket) {
        delete _clientSocket;
        _clientSocket = NULL;
    }
    
    
    // ken: FIXME: Clear the previous connection
    _clientSocket = new SNSocket();
    _clientSocket->createTCP();
    //_clientSocket->setNonBlock(true);
}

//SNHostStatetIdle,
//SNHostStatetWaitForClient,            // after bindPort and before accept
//SNHostStatetConnected,                // after accepted
void SNClient::checkNetwork()
{
    if(SNClientStateIdle == _state) {
    } else if(SNClientStatetConnected == _state) {
        checkNetworkWhenConnect();
    }
}

void SNClient::checkNetworkWhenConnect()
{
    checkIncomingData();
}

bool SNClient::checkIncomingData()
{
    if(_session == NULL) {
        log("checkIncomingData: session is NULL");
        return false;
    }
    
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
