//
//  SNRequestServer.h
//  NetEngine
//
//  Created by kenlee on 8/3/2021.
//

#ifndef SNRequestServer_h
#define SNRequestServer_h

#include <stdio.h>
#include <memory>

namespace simpleNet {

class SNSessionFactory;

class SNRequestServer {
public:
    // void setSessionFactory(SNSessionFactory *factory);
    
    void setSessionFactory(std::shared_ptr<SNSessionFactory> factory);
    
    void start(int port);
    
private:
    SNSessionFactory* _factory = NULL;
    std::shared_ptr<SNSessionFactory> _factoryPtr;
    int _port = 0;
};

}

#endif /* SNRequestServer_h */
