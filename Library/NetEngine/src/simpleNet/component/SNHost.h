//
//  SNHostComponent.h
//  SimpleNet
//
//  Created by kenlee on 13/3/2021.
//

#ifndef SNHostComponent_h
#define SNHostComponent_h

#include <stdio.h>
#include "SNNetBase.h"

namespace simpleNet {

class SNSessionFactory;
class SNSession;
class SNSocket;
class SNString;

enum SNHostState {
    SNHostStateIdle,
    SNHostStatetWaitForClient,            // after bindPort and before accept
    SNHostStatetConnected,                // after accepted
};


class SNHost : public SNNetBase {
public:
    SNHost();
    //void setSessionFactory(SNSessionFactory *factory);
    bool bindPort(int port);
    void checkNetwork();           // ken: is it a good method name?
    bool isConnectingClient();
//    void sendDataOut();
//    void queueToOutBuffer(SNString &str);
    
    // SNSession *getSession();        // ken: ???: should use const SNSession?
private:
//    SNSessionFactory* _factory = NULL;
//    SNSession *_session = NULL;         // connected session
//    SNSocket *_clientSocket = NULL;           // connected socket
    SNSocket *_serverSocket = nullptr;
    int _port = 0;
    SNHostState _state;
    
private:
    void initServerSocket();
    void initClientSocket();
    
    bool attemptAccept();       // true if successfully accepted
    //bool checkIncomingData();         // false if connection broken

    void checkNetworkWhenWaitClient();
    void checkNetworkWhenConnect();
};

}

#endif /* SNHostComponent_h */
