//
//  SNRequestServer.c
//  NetEngine
//
//  A simple server like HTTP, the session will process the incoming request
//  and reply with a response
//
//  Created by kenlee on 8/3/2021.
//

#include "SNRequestServer.h"
#include "../SNSessionFactory.h"
#include "../SNSocket.h"
#include <iostream>

namespace simpleNet {
    
void SNRequestServer::setSessionFactory(SNSessionFactory *factory)
{
    _factory = factory;
}

void SNRequestServer::start(int port)
{
    _port = port;
    
    if(_factory == NULL) {
        std::cout << "RequestServer: sessionFactory undefined\n";
        return;
    }
    
    //
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(_port);

    // Create the TCP
    SNSocket serverSocket;
    serverSocket.createTCP();
    if(serverSocket.bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return;
    }
    
    if(serverSocket.listen(10) == false) {
        std::cout << "Fail to listen\n";
        return;
    }
    
    SNSocket clientSocket;
    
    bool isAccepted = serverSocket.accept(clientSocket);
    if(isAccepted == false) {
        std::cout << "Client fail to accept\n";
        return;
    }
    
    std::cout << "Client success to accept\n";
    
    SNSession *session = _factory->create(&clientSocket);
    session->setConnected(/* isHost */ true); 

    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        if(session->isAlive() == false) {
            break;
        }
        session->receiveData();  // ken: sleep inside if no data received
    }
    
    
    serverSocket.close();
}

    
    
} // End of Namespace 
