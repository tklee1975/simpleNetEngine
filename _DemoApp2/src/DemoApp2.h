//
//  SimpleNetApp.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SimpleNetApp_h
#define SimpleNetApp_h

#include <stdio.h>
#include <simpleNet/CoreLib.h>
#include <simpleNet/NetEngine.h>
#include <ImguiHelper.h>
#include "Demo2AppPacket.h"
#include "DemoApp2Session.h"
//#include "SimpleNetAppSession.h"

const int kCmdMove = 100;
const int kCmdBullet = 101;
const int kCmdPlayerHit = 102;
const int kCmdRemoveBullet = 103;

using namespace simpleNet;


class DemoApp2 : public BaseImguiApp {
public:     
    enum class AppState {
        Idle,
        CreateHost,
        WaitClient,
        JoinHost,
        Connected,
        Test
    };
    
    enum class Dir {
        None,
        Up,
        Down,
        Left,
        Right,
    };

    struct Player {
        int _id;
        int x;
        int y;
        Dir dir;
        int score;
    };
    
    struct Bullet {
        i32 _id;
        i8 pid;
        int x;
        int y;
        i16 speedX;
        i16 speedY;
        bool isRemote;
        bool isDeleted;
    };

    friend DemoApp2Session;
    
public:
    DemoApp2();
    virtual void onInit();
    virtual void onUpdate(double delta);
    
    // ken: for communication to netSession
    void onConnected();
    
    
private:
    ImVec2 _posP1;
    ImVec2 _posP2;
    Player _player1;
    Player _player2;
    i8 _currentPid;
    
    i32 _bulletID;
    SNVector<Bullet> _bulletList;
    SNParticleSystem _pSystem;
    
    AppState _state;
    SNHost _host;
    SNClient _client;    
    bool _isHost;
    int _port;
    SNSocketAddr _sockAddr;
    
    SNString _errorMsg;
    bool _isBindPortSuccess;
    
    int _cmdCounter;
    double _fireCooldown = 0;
    
//    SimpleSessionFactory _hostFactory;
//    SimpleSessionFactory _clientFactory;
//    
    // --- internal Methods
    
    
    void handleInput(double delta);
    void movePlayer(i8 pid, ImVec2 change, Dir _dir, bool sendCmd);
    void hitPlayer(i8 pid);
    void removeBullet(i8 pid, i32 bulletID);
    void initPlayers();
    
    void checkBulletHit();
    void handleBulletHit(i8 pid, i32 bulletID);
    
    // Gui
    void drawGui();
    void drawGuiIdle();
    void drawGuiHost();
    void drawGuiClient();
    void drawGuiConnected();
    void drawGuiCreateHost();
    void drawGuiTest();
    void drawPlayer(const Player &player, const ImColor &color);
    
    void drawShapes();
    void createHitParticle(const ImVec2 &pos);
    
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
    
    void sendMoveCommand(int deltaX, int deltaY, Dir dir);
    void sendBulletCommand(const Bullet &bullet);
    void sendPlayerHitCommand(i8 pid);
    void sendRemoveBulletCommand(i8 pid, i32 bulletID);
    
    // Bullet
    void addBulletAtPos(int pid, int x, int y, Dir dir);
    void addBullet(int pid, int x, int y, int speedX, int speedY, bool sendToNet);
    void addBulletFromNet(i8 pid, i32 bulletID,
                        int x, int y, int speedX, int speedY);
    void updateBullets(double delta);
    void drawBullet(const Bullet &bullet);
    void drawAllBullets();
    void fireBullet(const Player &player, double delta);

    
    
    bool shouldSendCmd(int pid);
    
    //
    bool setupSockAddress(SNString &str, int port);
    
};




#endif /* SimpleNetApp_h */