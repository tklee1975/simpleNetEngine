
#include "SNNetBase.h"
#include "../SNSessionFactory.h"
#include "../SNSocket.h"
#include <iostream>


namespace simpleNet {


SNNetBase::SNNetBase()
{
}
    
void SNNetBase::setSessionFactory(std::shared_ptr<SNSessionFactory> factory)
{
    _factory = factory;
}

SNSession *SNNetBase::getSession()
{
    return nullptr;// _session; // ken: not use
}


void SNNetBase::initSocket()
{
    // release current
//    if(_mainSocket) {
//        delete _mainSocket;
//        _mainSocket = NULL;
//    }
//    
//    
//    // ken: FIXME: Clear the previous connection
//    _mainSocket = new SNSocket();
//    _mainSocket->createTCP();
//    
}

bool SNNetBase::createMainSession(SNSocket &&_sock)
{
    if(_factory == nullptr) {
        ERROR_LOG("createMainSession: factory is null");
        return false;
    }
    
    _mainSession = _factory->newSession(std::move(_sock));
    
    return _mainSession != nullptr;
}

bool SNNetBase::checkIncomingData()
{
    if(_mainSession == nullptr) {
        LOG("checkIncomingData: _mainSession is NULL");
        return false;
    }
    
    // log("Checking Incoming data");
    //size_t nRead = 0;
    if(_mainSession->isConncting() == false) {  // check for data
        LOG("checkIncomingData: No connecting");
        return false;
    }
    
    // log("Checking receive data");
    _mainSession->receiveData();
    
    
    
    return true;
}


void SNNetBase::queueToOutBuffer(SNString &str)
{
    if(str.str().size() == 0) {
        LOG("queueToOutBuffer: input is empty");
        return;
    }
    
    if(_mainSession) {
        _mainSession->putBufferWithStr(str);
    }
}

void SNNetBase::sendDataOut()
{
    
    if(_mainSession == nullptr) {   // session not yet ready 
        //LOG("session is null");
        return;
    }
    
    _mainSession->flushBuffer();
}

    
} // End of Namespace
