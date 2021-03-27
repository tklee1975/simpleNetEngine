//
//  SNClient.c
//  NetEngine
//
//  Created by kenlee on 13/3/2021.
//

#include "SNClient.h"
#include "../SNSessionFactory.h"
#include "../SNSocket.h"
#include <iostream>
#include <memory>

using namespace std;

namespace simpleNet {


SNClient::SNClient() : SNNetBase()
{
    _state = SNClientStateIdle;
}

bool SNClient::connectServer(const SNSocketAddr &addr)
{
//    if(_factory == nullptr) {
//        std::cout << "SNClient: sessionFactory undefined\n";
//        return false;
//    }
//    
    SNSocket newSock;
    
    newSock.createTCP();
    newSock.connect(addr);
    newSock.setNonBlock(true);
    
    createMainSession(std::move(newSock));
    _mainSession->setConnected(/* isHost */ false);
    
//    
//    
//    //
//    // Get the socket reference
//    initSocket();
//    
//    
//    _mainSocket->connect(addr);
//    _mainSocket->setNonBlock(true);
//    // Create the TCP
//    
//    
//    SNSocket socket;
//    socket.connect(addr);
//    socket.setNonBlock(true);
//    //auto socketPtr = make_unique<SNSocket>(&socket);
//    
//    //_session = _factory->create(socketPtr);
//    _session->setConnected(/* isHost */ false);
//    
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
