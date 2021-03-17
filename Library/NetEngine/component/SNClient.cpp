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


SNClient::SNClient() : SNNetBase()
{
    _state = SNClientStateIdle;
}
//    
//void SNClient::setSessionFactory(SNSessionFactory *factory)
//{
//    _factory = factory;
//}

bool SNClient::connectServer(const SNSocketAddr &addr)
{
    if(_factory == NULL) {
        std::cout << "SNClient: sessionFactory undefined\n";
        return false;
    }
    
    //
    // Get the socket reference
    initSocket();
    
    
    _mainSocket->connect(addr);
    _mainSocket->setNonBlock(true);
    // Create the TCP
    
    
    
    _session = _factory->create(_mainSocket);
    _session->setConnected(/* isHost */ false);
    
    _state = SNClientStatetConnected;
    
    return true;
}

//
//void SNClient::initClientSocket()
//{
//    // release current
//    if(_clientSocket) {
//        delete _clientSocket;
//        _clientSocket = NULL;
//    }
//
//
//    // ken: FIXME: Clear the previous connection
//    _clientSocket = new SNSocket();
//    _clientSocket->createTCP();
//    //_clientSocket->setNonBlock(true);
//}

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

    
} // End of Namespace
