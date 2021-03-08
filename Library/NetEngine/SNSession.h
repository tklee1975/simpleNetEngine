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
#include <CoreLib.h>

#include "SNSocket.h"


namespace simpleNet {

class SNSession {
public:
    SNSession(SNSocket *socket);
    ~SNSession();

    SNSocket *_socket;
    
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead); // ken: use & reference to save copy
    
    void sendData(std::vector<char> &dataBuf);
    void sendString(SNString &str);     // ken: is sendString(SNString *str) better??
    
    void close();
    bool isAlive();
    void receiveData();
    
private:
    std::vector<char> _outBuffer;
    std::vector<char> _inBuffer;
    bool _isAlive;
    
    size_t availableBytesToRead();
};


}

#endif /* SNSession_h */
