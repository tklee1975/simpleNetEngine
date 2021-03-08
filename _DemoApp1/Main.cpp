#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fmt/core.h>
#include "pch.h"

#include <NetEngine.h>
#include <CoreLib.h>
#include "SimpleSocketServer.h"


void startSocketServer() {
    auto server = SimpleSocketServer();
    
    server.start(1234);
}

void startEchoServer() {
    auto server = simpleNet::SNRequestServer();
    auto sessionFactory = new simpleNet::SNEchoSessionFactory();
    
    server.setSessionFactory(sessionFactory);
    server.start(1234);
}


int main() {
    fmt::print("Simple Network Engine\n");
    fmt::print("Corelib Version: {}.\n", KC_CORE_LIB_VERSION);
    fmt::print("NetEngine Version: {}.\n", KC_NET_ENGINE_VERSION);
    
    //simpleNet::log("Server is started!");
    //startSocketServer();
    startEchoServer();
    
    return 0;
}
