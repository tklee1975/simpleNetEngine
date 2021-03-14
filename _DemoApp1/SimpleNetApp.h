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
    SimpleNetAppStateWaitClient = 1,
    SimpleNetAppStateJoinHost = 2,
    SimpleNetAppStateConnected = 3,
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
    
    SNString _errorMsg;
    bool _isBindPortSuccess;
    
    void drawShapes();
    
    void handleInput(double delta);
    void movePlayer(int pid, ImVec2 change);

    // Gui
    void drawGui();
    void drawGuiIdle();
    void drawGuiHost();
    void drawGuiClient();
    void drawGuiConnected();
    
    // Create room / setup host
    void onCreateRoomClicked();
    void setupHost();

    //
    void onUpdateWaitClient(double delta);
    void onUpdateConnected(double delta);
};




#endif /* SimpleNetApp_h */
