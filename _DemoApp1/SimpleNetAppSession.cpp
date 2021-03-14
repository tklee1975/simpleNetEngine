//
//  SimpleNetAppSession.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "SimpleNetAppSession.h"
#include "SimpleNetApp.h"

SimpleHostSession::SimpleHostSession(SNSocket *sock) : SNSession(sock)
{

}

void SimpleHostSession::onConnect()
{
    std::cout << "Connected to client\n";
    if(app != nullptr) {
        app->onConnected();
    }
}

void SimpleHostSession::onDisconnect()
{
    std::cout << "Client disconnected\n";
}

void SimpleHostSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    if(app == nullptr) {
        return;
    }
    
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "RECEIVE: " << msg << "\n";
    if(strlen(msg) == 0) {
        return;
    }
    
    //
    SNString cmd;
    if(msg[0] == 'u'){
        cmd.set("up");
    } else if(msg[0] == 'd') {
        cmd.set("down");
    } else if(msg[0] == 'l') {
        cmd.set("left");
    } else if(msg[0] == 'r') {
        cmd.set("right");
    } else {
        cmd = SNString(msg);
    }
    
    if(cmd.isEmpty() == false) {
        app->onReceiveCommand(cmd);
    }
}
