//
//  SNClient.h
//  NetEngine
//
//  Created by kenlee on 13/3/2021.
//

#ifndef SNClient_h
#define SNClient_h

#include <stdio.h>

namespace simpleNet {

enum SNClientState {
    SNClientStateIdle,
    SNClientStatetConnected,                // after accepted
};


class SNSessionFactory;
class SNSession;
class SNSocket;
class SNSocketAddr;



class SNClient {
public:
    SNClient();
    void setSessionFactory(SNSessionFactory *factory);
    bool connectServer(const SNSocketAddr &addr);
    void checkNetwork();           // ken: is it a good method name?
    SNSession *getSession();        // ken: ???: should use const SNSession?
    
private:
    SNSessionFactory* _factory = NULL;
    SNSession *_session = NULL;         // connected session
    SNSocket *_clientSocket = NULL;           // connected socket
    SNClientState _state;
    
private:
    void initClientSocket();
    void checkNetworkWhenConnect();
    
    bool checkIncomingData();         // false if connection broken

    
};

}


#endif /* SNClient_h */
