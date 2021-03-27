//
//  SNSessionFactory.h
//  SimpleNet
//
//  Created by kenlee on 7/3/2021.
//

#ifndef SNSessionFactory_h
#define SNSessionFactory_h

#include <stdio.h>
#include <memory>
#include "SNSession.h"
#include "SNSocket.h"

namespace simpleNet {
    

class SNSessionFactory
{
public:
    SNSessionFactory() {} 
//    virtual SNSession *create(SNSocket *socket) {
//        return nullptr;
//    }
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) {
        return nullptr;
    }
};

}

#endif /* SNSessionFactory_h */
