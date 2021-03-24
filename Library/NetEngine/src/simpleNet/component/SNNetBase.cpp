
#include "SNNetBase.h"
#include "../SNSessionFactory.h"
#include "../SNSocket.h"
#include <iostream>


namespace simpleNet {


SNNetBase::SNNetBase()
{
}
    
void SNNetBase::setSessionFactory(SNSessionFactory *factory)
{
    _factory = factory;
}

SNSession *SNNetBase::getSession()
{
    return _session;
}


void SNNetBase::initSocket()
{
    // release current
    if(_mainSocket) {
        delete _mainSocket;
        _mainSocket = NULL;
    }
    
    
    // ken: FIXME: Clear the previous connection
    _mainSocket = new SNSocket();
    _mainSocket->createTCP();
    //_clientSocket->setNonBlock(true);
}

bool SNNetBase::checkIncomingData()
{
    if(_session == NULL) {
        LOG("checkIncomingData: session is NULL");
        return false;
    }
    
    // log("Checking Incoming data");
    size_t nRead = 0;
    if(_session->isConncting(nRead) == false) {  // check for data
        return false;
    }
    
    // log("Checking receive data");
    _session->receiveData();
    
    return true;
}


void SNNetBase::queueToOutBuffer(SNString &str)
{
    if(str.str().size() == 0) {
        return;
    }
    
    if(_session != NULL) {
        _session->putBufferWithStr(str);
    }
}

void SNNetBase::sendDataOut()
{
    if(_session == NULL) {
        return;
    }
    
    _session->flushBuffer();
}

    
} // End of Namespace
