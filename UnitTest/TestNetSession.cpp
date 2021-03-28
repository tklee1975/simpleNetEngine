//
//  TestNetSession.c
//  test_main
//
//  Created by kenlee on 11/3/2021.
//

#include "TestNetSession.h"

using namespace simpleNet;

TestHttpGetSession::TestHttpGetSession(SNSocket &&sock)
    : SNSession(std::move(sock))
{
    
}

void TestHttpGetSession::onConnect()
{
    std::cout << "Session Connected\n";
    
    char command[] = "GET /index.html \r\n\r\n";
    //_mySocket.send(command, strlen(command));
    sendString(command);
    //flushBuffer();
}

void TestHttpGetSession::onRecvData(std::vector<u8> &buf, size_t &nRead)
{
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "REPLY FROM Server:\n" << msg << "\n";
    
    //std::cout << "Please enter something to send\n";
    //std::string input;
    
    //std::cin >> input;
    
    //SNString returnStr = SNString(input.c_str());
    
    //sendString(returnStr);
}


// --------------- 


//TestEchoClientSession(SNSocket &&);
TestEchoClientSession::TestEchoClientSession(SNSocket &&sock)
    : SNSession(std::move(sock))
{
    
}

void TestEchoClientSession::onConnect()
{
}

void TestEchoClientSession::onRecvData(std::vector<u8> &buf, size_t &nRead)
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

SampleNetSession::SampleNetSession(SNSocket &&sock)
    : SNSession(std::move(sock))
{
    _counter = 0;
}

//
//SampleNetSession::SampleNetSession(SNSocket *sock) : SNSession(sock)
//{
//    _counter = 0;
//
//}

void SampleNetSession::onConnect()
{
    std::cout << "Connected to client\n";
    _counter = 0;
}

void SampleNetSession::onDisconnect()
{
    std::cout << "Client disconnected\n";
}

void SampleNetSession::onRecvData(std::vector<u8> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "RECEIVE: " << msg << "\n";
}



SampleNetClientSession::SampleNetClientSession(SNSocket &&sock)
    : SNSession(std::move(sock))
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

void SampleNetClientSession::onRecvData(std::vector<u8> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    buf[nRead] = '\0';
    const char *msg = (const char *) buf.data();
    std::cout << "RECEIVE: " << msg << "\n";
}
