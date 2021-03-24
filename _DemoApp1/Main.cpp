#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fmt/core.h>
#include "pch.h"
//
//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//#include <SDL.h>


#include <simpleNet/NetEngine.h>
#include <simpleNet/CoreLib.h>
#include "SimpleSocketServer.h"
#include "SimpleNetApp.h"




void startSocketServer() {
    auto server = SimpleSocketServer();
    
    server.start(1234);
}

void startEchoServer() {
    auto server = simpleNet::SNRequestServer();
    auto sessionFactory = new simpleNet::SNEchoSessionFactory();
    
    server.setSessionFactory(sessionFactory);
    server.start(2345);
}

void startSimpleNetApp() {
    auto app = SimpleNetApp();
    if(app.init() == false) {
        std::cout << "Fail to init\n";
        return;
    }
    
    app.run();
}


int main() {
    fmt::print("Simple Network Engine\n");
    fmt::print("Corelib Version: {}.\n", KC_CORE_LIB_VERSION);
    fmt::print("NetEngine Version: {}.\n", KC_NET_ENGINE_VERSION);
    
    //simpleNet::log("Server is started!");
    //startSocketServer();
    // startEchoServer();
    startSimpleNetApp();
    
    return 0;
}
