#ifndef SNNetBase_hpp
#define SNNetBase_hpp

#include <stdio.h>

namespace simpleNet {



class SNSessionFactory;
class SNSession;
class SNSocket;
class SNSocketAddr;
class SNString;

class SNNetBase {
public:
    SNNetBase();
    void setSessionFactory(SNSessionFactory *factory);
    
    SNSession *getSession();        // ken: ???: should use const SNSession?
    void sendDataOut();
    void queueToOutBuffer(SNString &str);
    bool checkIncomingData();         // false if connection broken
    

protected:
    SNSessionFactory* _factory = NULL;
    SNSession *_session = NULL;         // connected session
    SNSocket *_mainSocket = NULL;           // connected socket
    
    void initSocket();
    
    
};

}

#endif
