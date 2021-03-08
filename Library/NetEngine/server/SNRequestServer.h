//
//  SNRequestServer.h
//  NetEngine
//
//  Created by kenlee on 8/3/2021.
//

#ifndef SNRequestServer_h
#define SNRequestServer_h

#include <stdio.h>

namespace simpleNet {

class SNSessionFactory;

class SNRequestServer {
public:
    void setSessionFactory(SNSessionFactory *factory);
    void start(int port);
    
private:
    SNSessionFactory* _factory = NULL;
    int _port = 0;
};

}

#endif /* SNRequestServer_h */
