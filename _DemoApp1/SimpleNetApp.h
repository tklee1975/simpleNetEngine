//
//  SimpleNetApp.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SimpleNetApp_h
#define SimpleNetApp_h

#include <stdio.h>
#include <CoreLib.h>
#include <NetEngine.h>
#include <ImguiHelper.h>

using namespace simpleNet;

enum SimpleNetAppState {
    SimpleNetAppStateIdle = 0,
    SimpleNetAppStateCreateHost = 1,
    SimpleNetAppStateWaitClient = 2,
    SimpleNetAppStateJoinHost = 3,
    SimpleNetAppStateConnected = 4,
};

class SimpleNetApp : public BaseImguiApp {
public:
    SimpleNetApp();
    virtual void onInit();
    virtual void onUpdate(double delta);
    
    // ken: for communication to netSession
    void onConnected();
    void onReceiveCommand(SNString &cmd);
    
private:
    ImVec2 _posP1;
    ImVec2 _posP2;
    
    SimpleNetAppState _state;
    SNHost _host;
    SNClient _client;    
    bool _isHost;
    int _port;
    SNSocketAddr _sockAddr;
    
    SNString _errorMsg;
    bool _isBindPortSuccess;
    
    int _cmdCounter;
    
    // --- internal Methods
    
    
    void handleInput(double delta);
    void movePlayer(int pid, ImVec2 change);

    // Gui
    void drawGui();
    void drawGuiIdle();
    void drawGuiHost();
    void drawGuiClient();
    void drawGuiConnected();
    void drawGuiCreateHost();
    
    void drawShapes();
    
    // Create room / setup host
    void onCreateRoomClicked();
    void onStartRoomClicked();
    
    void onJoinHostClicked();
    void setupHost();
    void setupClient();

    //
    void onUpdateWaitClient(double delta);
    void onUpdateConnected(double delta);
    
    //
    void handleMoveCommand(SNString &cmd);
    void sendCommand(SNString &cmd);
    void sendMoveCommand(int deltaX, int deltaY);
    
    bool setupSockAddress(SNString &str, int port);
};




#endif /* SimpleNetApp_h */
