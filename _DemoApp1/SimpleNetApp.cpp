//
//  SimpleNetApp.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "SimpleNetApp.h"
#include "SimpleNetAppSession.h"

#include <iostream>

const int kPort = 4567;

SimpleNetApp::SimpleNetApp(){
    _host = SNHost();
    _client = SNClient();
    
    _errorMsg = SNString("");
}

//https://www.programmersought.com/article/85304753942/
void SimpleNetApp::drawShapes()
{

    // Active position position
    SNShapeHelper::drawRectAtCenter(_posP1, 30, SN_YELLOW);
    
    SNShapeHelper::drawRectAtCenter(_posP2, 30, SN_PURPLE);
    //SNShapeHelper::drawRectAtCenter(ImVec2(100, 250), 50, ImColor(0, 255, 0));
}

void SimpleNetApp::onInit()
{
    _state = SimpleNetAppStateIdle;
    
    _clearColor = ImVec4(0.5f, 0.5f, 0.50f, 1.00f);
    
    _posP1 = ImVec2(100, 300);
    _posP2 = ImVec2(300, 300);
}

void SimpleNetApp::onUpdate(double delta)
{
    
    handleInput(delta);
    
    
    if(SimpleNetAppStateWaitClient == _state) {
        onUpdateWaitClient(delta);
    } else if(SimpleNetAppStateConnected == _state) {
        onUpdateConnected(delta);
    }
//
//    // GUI Handling
//    // A new window
//    ImGui::Begin("Testing Primitive!"); // Create a window called "Hello, world!" and append into it.
//
//
//    if (ImGui::Button("Button A")) {
//        std::cout << "'Button A' is clicked\n";
//    }
//    ImGui::Text("Text Line 1");
//    ImGui::Text("Text Line 2");
//    ImGui::Text("Text Line with variable %s", "hello");
//    ImGui::End();
//
    // END of GUI Handling
    drawGui();
    
    drawShapes();
}




void SimpleNetApp::drawGuiIdle()
{
    if (ImGui::Button("Create Room (Host)")) {
        //std::cout << "'Button A' is clicked\n";
        onCreateRoomClicked();
    }
    
    if (ImGui::Button("Join Room (Client)")) {
        //std::cout << "'Button A' is clicked\n";
        _errorMsg.set("");
        _state = SimpleNetAppStateJoinHost;
    }
}


void SimpleNetApp::onCreateRoomClicked()
{
    setupHost();
    _state = SimpleNetAppStateWaitClient;
    
}

void SimpleNetApp::onJoinHostClicked()
{
    setupClient();
    
}

void SimpleNetApp::drawGuiHost()
{
    ImGui::Text("Waiting client to join");
    ImGui::Text("Host location: locahost:%d", kPort);
    ImGui::NewLine();
    if(! _errorMsg.isEmpty()) {
        ImGui::Text("%s", _errorMsg.c_str());
        
        ImGui::NewLine();
        
        if (ImGui::Button("Recreate Host")) {
            //std::cout << "'Button A' is clicked\n";
            onCreateRoomClicked();
        }
    }
    
}

void SimpleNetApp::drawGuiClient()
{
    ImGui::Text("Enter the location to join");
    
    if (ImGui::Button("Join Host")) {
        //std::cout << "'Button A' is clicked\n";
        onJoinHostClicked();
    }
    
    if(! _errorMsg.isEmpty()) {
        ImGui::Text("%s", _errorMsg.c_str());
      
    }
}

void SimpleNetApp::drawGuiConnected()
{
    ImGui::Text("Players are connected");
}


void SimpleNetApp::drawGui()
{
    ImGui::Begin("Control Panel");
    
    if(SimpleNetAppStateIdle == _state) {
        drawGuiIdle();
    } else if(SimpleNetAppStateWaitClient == _state) {
        drawGuiHost();
    } else if(SimpleNetAppStateJoinHost == _state) {
        drawGuiClient();
    } else if(SimpleNetAppStateConnected == _state) {
        drawGuiConnected();
    }
    
    ImGui::End();
}

void SimpleNetApp::movePlayer(int pid, ImVec2 change)
{
    ImVec2 &pos = (pid == 0) ? _posP1 : _posP2;
    int deltaX = (int) change.x;
    int deltaY = (int) change.y;
    
    
    pos.x += deltaX;
    pos.y += deltaY;
    
    bool shouldSendCommand = (pid == 0 && _isHost == true)  // host send to client
                        || (pid == 1 && _isHost == false);   // client send to host
    // log("shouldSendCommand: %d", shouldSendCommand);
    if(shouldSendCommand) {
        sendMoveCommand(deltaX, deltaY);
    }
}

void SimpleNetApp::handleInput(double deltaTime)
{
    if(SimpleNetAppStateConnected != _state) {
        return;
    }
    
    ImVec2 dir {0,0};
    float speed = 200;

    if (getInputKey(SDLK_w)) dir.y -= 1;
    if (getInputKey(SDLK_s)) dir.y += 1;
    if (getInputKey(SDLK_a)) dir.x -= 1;
    if (getInputKey(SDLK_d)) dir.x += 1;

    if(dir.x == 0 && dir.y == 0) {
        return;
    }
    
    ImVec2 change;
    
    change.x = dir.x * deltaTime * speed;
    change.y = dir.y * deltaTime * speed;
    
    int pid = _isHost ? 0 : 1;
    movePlayer(pid, change);
}

void SimpleNetApp::setupHost()
{
    auto factory = new SimpleSessionFactory(this, true);
    _host.setSessionFactory(factory);
    bool isSuccess = _host.bindPort(kPort);
    
    if(isSuccess == false) {
        _errorMsg.set("Fail to bind the port");
        _isBindPortSuccess = false;
        return;
    }
    
    _isHost = true;
    _isBindPortSuccess = true;
}

void SimpleNetApp::setupClient()
{
    _client.setSessionFactory(new SimpleSessionFactory(this, false));
    
    SNSocketAddr addr;
    addr.setIPv4(127, 0, 0, 1);
    addr.setPort(kPort);
    
    
    bool isSuccess = _client.connectServer(addr);
    if(isSuccess == false) {
        _errorMsg.set("Fail to connect the server");
        std::cout << "Fail to connect the server. err: " << errno << "\n";
        return;
    }

    _state = SimpleNetAppStateConnected;
//    int counter = 0;
//    std::cout << "Starting the Network Loop\n";
//    for(;;) {
//        client.checkNetwork();
//        counter++;
//
//        if((counter % 500000) == 0) {
//            SNSession *session = client.getSession();
//            if(session != NULL) {
//                session->sendString("Client: tick passed\n");
//            }
//            //host.getSession()->sendString("100 tick passed");
//            //sendString("100 tick passed");
//        }
//        //sleep(1);
//    }
}

void SimpleNetApp::onConnected()
{
    _state = SimpleNetAppStateConnected;
}

void SimpleNetApp::onReceiveCommand(SNString &cmd)
{
    log("onReceiveCommand: %s", cmd.c_str());
    if(cmd.str() == "up") {
        movePlayer(1, ImVec2(0, -30));
    } else if(cmd.str() == "down") {
        movePlayer(1, ImVec2(0, 30));
    } else if(cmd.str() == "left") {
        movePlayer(1, ImVec2(-30, 0));
    } else if(cmd.str() == "right") {
        movePlayer(1, ImVec2(30, 0));
    } else if(cmd.startsWith("move")){
        handleMoveCommand(cmd);
    }
}

void SimpleNetApp::handleMoveCommand(SNString &cmd)
{
    cmd.rtrim();
    
    std::vector<SNString> tokens = cmd.split(" ");
    if(tokens.size() < 3) {
        log("handleMoveCommand: incorrect token count");
        return;
    }
    int moveX = tokens[1].toInt();
    int moveY = tokens[2].toInt();
    
    int pid = _isHost ? 1 : 0;  //
    movePlayer(pid, ImVec2(moveX, moveY));
}

void SimpleNetApp::onUpdateWaitClient(double delta)
{
    
    if(_isBindPortSuccess == false) {
        return;
    }
    // log("Checking Network");
    _host.checkNetwork();   // ken: will callback onConnect if client connected
}

void SimpleNetApp::onUpdateConnected(double delta)
{
    if(_isHost) {
        _host.checkNetwork();
    } else {
        _client.checkNetwork();
    }
}

void SimpleNetApp::sendMoveCommand(int deltaX, int deltaY)
{
    SNString cmd = SNString("move");
    char value[100];
    sprintf(value, " %d", deltaX);
    cmd.append(value);
    
    sprintf(value, " %d", deltaY);
    cmd.append(value);
    cmd.append("\n");
    
    std::cout << "Command: " << cmd.str() << "\n";
    
    sendCommand(cmd);
}

void SimpleNetApp::sendCommand(SNString &cmd)
{
    if(_isHost) {
        if(_host.getSession() == NULL) {
            log("SimpleNetApp.sendCommand: host.session not ready");
            return;
        }
        
        _host.getSession()->sendString(cmd);
    } else {
        if(_client.getSession() == NULL) {
            log("SimpleNetApp.sendCommand: client.session not ready");
            return;
        }
        _client.getSession()->sendString(cmd);
    }
}
