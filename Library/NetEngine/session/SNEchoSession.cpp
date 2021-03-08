//
//  SNEchoSession.c
//  NetEngine
//
//  Created by kenlee on 7/3/2021.
//

#include "SNEchoSession.h"
namespace simpleNet {

SNEchoSession::SNEchoSession(SNSocket *sock) : SNSession(sock)
{
}


void SNEchoSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    const char *msg = (const char *) buf.data();
    std::cout << " input: " << msg << "\n";

    SNString returnMsg = SNString("ECHO: ");
    returnMsg.append(msg);
 
    sendString(returnMsg);
}


} // end of namespace
