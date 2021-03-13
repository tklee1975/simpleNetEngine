//
//  SNEchoSession.h
//  NetEngine
//
//  Created by kenlee on 7/3/2021.
//

#ifndef SNEchoSession_h
#define SNEchoSession_h

#include <stdio.h>
#include "SNSession.h"
#include "SNSessionFactory.h"

namespace simpleNet {
    
class SNEchoSession : public SNSession {
public:
    SNEchoSession(SNSocket *);
    
protected:
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead);
    virtual void onConnect();
};

class SNEchoSessionFactory : public SNSessionFactory {
public:
    virtual SNSession *create(SNSocket *socket) {
        return new SNEchoSession(socket);
    }
};

}


#endif /* SNEchoSession_h */
