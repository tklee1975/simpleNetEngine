//
//  SNSession.h
//  SimpleNet
//
//  Created by kenlee on 7/3/2021.
//

#ifndef SNSession_h
#define SNSession_h

#include <stdio.h>
#include <vector>
#include <simpleNet/CoreLib.h>

#include "SNSocket.h"


namespace simpleNet {

class SNSession {
public:
    SNSession(SNSocket *socket);
    ~SNSession();

    SNSocket *_socket = nullptr;      // ken: the socketing connecting the client or server
    bool isHost;           
    
    
    
    size_t sendData(std::vector<u8> &dataBuf);
    void sendString(SNString &str);     // ken: is sendString(SNString *str) better??
    void sendString(const char *str);
    
    
    void setNonblock(bool flag);
    void setConnected(bool isHost);
    void close();
    bool isAlive();
    bool hasData();
    bool isConncting(size_t &availableByte);
    void receiveData();
    void putBufferWithStr(SNString &str);
    void flushBuffer();
    
protected:  // implemented by the subclass
    virtual void onConnect() = 0;
    virtual void onDisconnect() {}
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead); // ken: use & reference to save copy
    
private:
    std::vector<u8> _outBuffer;
    std::vector<u8> _inBuffer;            // ken: use to store the incoming buffer
    bool _isAlive;
    
    
    size_t availableBytesToRead();
};


}

#endif /* SNSession_h */
