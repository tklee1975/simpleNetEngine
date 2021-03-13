//
//  TestNetSession.c
//  test_main
//
//  Created by kenlee on 11/3/2021.
//

#include "TestNetSession.h"

using namespace simpleNet;

TestEchoClientSession::TestEchoClientSession(SNSocket *sock) : SNSession(sock)
{
    
}

void TestEchoClientSession::onConnect()
{
}

void TestEchoClientSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "REPLY FROM Server: " << msg << "\n";
    
    std::cout << "Please enter something to send\n";
    std::string input;
    
    std::cin >> input;
    
    SNString returnStr = SNString(input.c_str());
    
    sendString(returnStr);
}


// --------------- 


SampleNetSession::SampleNetSession(SNSocket *sock) : SNSession(sock)
{
    _counter = 0;

}

void SampleNetSession::onConnect()
{
    std::cout << "Connected to client\n";
    _counter = 0;
}

void SampleNetSession::onDisconnect()
{
    std::cout << "Client disconnected\n";
}

void SampleNetSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "RECEIVE: " << msg << "\n";
}




SampleNetClientSession::SampleNetClientSession(SNSocket *sock) : SNSession(sock)
{
    _counter = 0;

}

void SampleNetClientSession::onConnect()
{
    std::cout << "Connected to client\n";
    _counter = 0;
}

void SampleNetClientSession::onDisconnect()
{
    std::cout << "Client disconnected\n";
}

void SampleNetClientSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "RECEIVE: " << msg << "\n";
}
