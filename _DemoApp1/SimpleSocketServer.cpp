//
//  SimpleSocketServer.c
//  app1
//
//  Created by kenlee on 7/3/2021.
//
#include "SimpleSocketServer.h"

#include <iostream>
#include <fmt/core.h>

// My Library
#include <CoreLib.h>
#include <NetEngine.h>

// 
using namespace simpleNet;
using namespace std;


void SimpleSocketServer::start(int port)
{
    std::cout << "Starting Socket Server at port " << port << "\n";
    
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(port);

    SNSocket serverSocket;
    serverSocket.createTCP();
    if(serverSocket.bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return;
    }
    if(serverSocket.listen(10) == false) {
        std::cout << "Fail to listen\n";
        return;
    }
    
    SNSocket clientSocket;
    
    bool isAccepted = serverSocket.accept(clientSocket);
    if(isAccepted == false) {
        std::cout << "Client fail to accept\n";
        return;
    }
    std::cout << "Client success to accept\n";
        
    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        size_t n = clientSocket.availableBytesToRead();
        if(n <= 0) {
            sleep(1);
            continue;
        }
        
        clientSocket.recv(buf, n);
        buf.push_back(0);   // add the character '\0' to make it a string

        
        
        //std::cout << "Byte Read: " << ((int) n) << " input: " << buf << "\n";
        const char *msg = (const char *) buf.data();
        std::cout << " input: " << msg << "\n";

        SNString returnMsg = SNString("ECHO: ");
        returnMsg.append(msg);
        
        //outBuf = "ECHO: ";
        returnMsg.copyTo(outBuf);
        
        clientSocket.send(outBuf.data(), outBuf.size());
    }
    
    
    clientSocket.close();
    serverSocket.close();
   
}
