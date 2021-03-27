//
//  SNEchoSession.h
//  NetEngine
//
//  Created by kenlee on 7/3/2021.
//

#ifndef SNEchoSession_h
#define SNEchoSession_h

#include <stdio.h>
#include "../SNSession.h"
#include "../SNSessionFactory.h"

namespace simpleNet {
    
class SNEchoSession : public SNSession {
public:
    SNEchoSession(SNSocket &&sock);
    
protected:
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
};

class SNEchoSessionFactory : public SNSessionFactory {
public:
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {
        return std::make_unique<SNEchoSession>(std::move(socket));
    }    
};

}


#endif /* SNEchoSession_h */
