#ifndef SNNetBase_hpp
#define SNNetBase_hpp

#include <stdio.h>
#include <memory>

namespace simpleNet {



class SNSessionFactory;
class SNSession;
class SNSocket;
class SNSocketAddr;
class SNString;

class SNNetBase {
public:
    SNNetBase();
    virtual ~SNNetBase() {} 
    void setSessionFactory(std::shared_ptr<SNSessionFactory> factory);
    
    SNSession *getSession();        // ken: ???: should use const SNSession?
    void sendDataOut();
    void queueToOutBuffer(SNString &str);
    bool checkIncomingData();         // false if connection broken
    

protected:
    std::shared_ptr<SNSessionFactory> _factory;
    
    void initSocket();
    
    std::unique_ptr<SNSession> _mainSession = nullptr;
    
    
    bool createMainSession(SNSocket &&_sock);
};

}

#endif
