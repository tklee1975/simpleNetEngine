//
//  SNSession.c
//  SimpleNet
//
//  Created by kenlee on 7/3/2021.
//

#include "SNSession.h"
#include <fcntl.h> /* Added for the nonblocking socket */

namespace simpleNet {


SNSession::SNSession(SNSocket *socket)
{
    _socket = socket;
    
    _isAlive = _socket == NULL ? false : true;
}

SNSession::~SNSession()
{
    if(! _socket) {
        _socket->close();
    }
}
    
void SNSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    // Need implemented by child class
    std::cout << "onRecvData: " << nRead << " bytes received\n";
}

void SNSession::sendData(std::vector<char> &dataBuf)
{
    _socket->send(dataBuf.data(), dataBuf.size());
}

size_t SNSession::availableBytesToRead()
{
    if(_socket == NULL) {
        return 0;
    }
    
    return _socket->availableBytesToRead();
}

void SNSession::setConnected(bool isHostFlag)
{
    isHost = isHostFlag;
    onConnect();
}

void SNSession::receiveData() {
    size_t nRead = availableBytesToRead();
    // log("SNSession.receiveData: nRead=%d", nRead);
    if(nRead == 0) {    // ken: nRead = 0 if not data retrieved at the moment
        //sleep(1);       // 1 second     //
        return;
    }
    
    _inBuffer.clear();
    _socket->recv(_inBuffer, nRead);
    _inBuffer.push_back(0);   // add the character '\0' to make it a string

    onRecvData(_inBuffer, nRead);
}


void SNSession::close() {
    _isAlive = false;
    if(! _socket) {
        _socket->close();
    }
}

bool SNSession::isConncting(size_t &availableByte)
{
    size_t result = availableBytesToRead();
    //log("SNSession.isConncting: nRead=%d", result);
    
    // KEN: todo: Check for disconnection
    
    
//    if(nRead == 0) {    // ken: nRead = 0 if not data retrieved at the moment
//        return false;
//    }
    availableByte = result;
    return true;
}

bool SNSession::isAlive() {
    //log("SNSession: isAlive: %d", _isAlive);
    return _isAlive;
}

void SNSession::sendString(const char *str)
{
    SNString s = SNString(str); // KEN: FIXME: how to write better?
    sendString(s);
}

void SNSession::sendString(SNString &str)
{
    _outBuffer.clear();
    str.copyTo(_outBuffer);
    
    sendData(_outBuffer);
}

} // end of namespace
