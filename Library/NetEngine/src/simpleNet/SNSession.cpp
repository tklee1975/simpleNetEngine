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
    if(_socket != NULL) {
        _socket->close();
    }
}
    
void SNSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    // Need implemented by child class
    std::cout << "onRecvData: " << nRead << " bytes received\n";
}

size_t SNSession::sendData(std::vector<char> &dataBuf)
{
    return _socket->send(dataBuf.data(), dataBuf.size());
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
    
    _socket->recv(_inBuffer, nRead);
    _inBuffer.push_back(0);   // add the character '\0' to make it a string

    std::string strValue = std::string(_inBuffer.begin(), _inBuffer.end());
    std::cout << "receiveData: " << strValue << "\n";
    
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

// http://www.kegel.com/dkftpbench/nonblocking.html
void SNSession::flushBuffer()
{
    int sendCount = sendData(_outBuffer);
    if(sendCount < 0) {
        ERROR_LOG("flushBuffer. sendData error");
        return;
    }
    
    
    if(sendCount > 0) {
        std::string strValue = std::string(_outBuffer.begin(), _outBuffer.end());
        std::cout << "flushBuffer: " << strValue << " count:"<< sendCount << "\n";
    }
    
    _outBuffer.erase(_outBuffer.begin(), _outBuffer.begin() + sendCount);
    //_outBuffer.clear();
}

void SNSession::putBufferWithStr(SNString &str)
{
    //_outBuffer.ins
    str.appendTo(_outBuffer);
}

void SNSession::sendString(SNString &str)
{
    // ken: TODO: Add a queue to prevent buffer ov

    
    str.copyTo(_outBuffer);     // the outBuffer is clear here...!!!
    
    // Reference here!!!
    sendData(_outBuffer);
}

} // end of namespace
