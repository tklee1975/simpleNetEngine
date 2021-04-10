//
//  DemoApp2.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "DemoApp2.h"
#include "DemoApp2Session.h"
#include "Demo2AppPacket.h"


#include <iostream>
#include <memory>

using namespace std;
using namespace simpleNet;

const int kPort = 4567;

const ImVec2 kP1BornPos(600, 50);
const ImVec2 kP2BornPos(50, 600);
const float kBulletSpeed = 350;
//const float kBulletSpeed = 50;
const float kBulletRadius = 10;
const float kTankSize = 20;


constexpr float square(float in) {
    return in * in;
}

const float kCheckHitSqr = square(kBulletRadius+ kTankSize);

DemoApp2::DemoApp2()
{
    _host.setSessionFactory(make_shared<DemoApp2SessionFactory>(*this, true));    // ken: is '*this' is used how to get my reference?
    _client.setSessionFactory(make_shared<DemoApp2SessionFactory>(*this, false));
    
    _errorMsg = SNString("");
    initPlayers();
    _bulletID = 1;
    _currentPid = 0;
}


void DemoApp2::initPlayers()
{
    _player1._id = 0;
    _player1.x = kP1BornPos.x;
    _player1.y = kP1BornPos.y;
    _player1.score = 0;
    _player1.dir = Dir::Down;
    
    _player2._id = 1;
    _player2.x = kP2BornPos.x;
    _player2.y = kP2BornPos.y;
    _player2.score = 0;
    _player2.dir = Dir::Up;
}

//https://www.programmersought.com/article/85304753942/
void DemoApp2::drawShapes()
{

    // Active position position
    SNShapeHelper::drawRectAtCenter(_posP1, 30, ColorYellow);
    
    SNShapeHelper::drawRectAtCenter(_posP2, 30, ColorPurple);
    //SNShapeHelper::drawRectAtCenter(ImVec2(100, 250), 50, ImColor(0, 255, 0));
}

void DemoApp2::createHitParticle(const ImVec2 &pos)
{
    SNParticle p(1);
    p.size = 40;
    p.pos = pos;
    p.color = ImColor(200, 200, 100);
    
    LOG("Add particle!!");
    _pSystem.addParticle(p);
}


void DemoApp2::drawPlayer(const Player &player, const ImColor &color)
{
    //auto* drawList = ImGui::GetBackgroundDrawList();
    //AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
    // Active position position
    ImColor turretColor = color == ColorRed ? ColorGreen : ColorPurple;
    
    ImVec2 pos(player.x, player.y);
    SNShapeHelper::drawRectAtCenter(pos, 40, color);

    // Draw the turret
    ImVec2 pos2(pos);
    int len = 30;
    if(player.dir == Dir::Up)           {   pos2.y -= len;   }
    else if(player.dir == Dir::Down)    {   pos2.y += len;   }
    else if(player.dir == Dir::Left)    {   pos2.x -= len;   }
    else if(player.dir == Dir::Right)   {   pos2.x += len;   }
    
    SNShapeHelper::drawRectAtCenter(pos, 20, turretColor);
    
    auto* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddLine(pos, pos2, turretColor, 10.0f);

    //SNShapeHelper::drawRectAtCenter(_posP2, 30, ColorPurple);
    //SNShapeHelper::drawRectAtCenter(ImVec2(100, 250), 50, ImColor(0, 255, 0));
}


void DemoApp2::onInit()
{
    _state = AppState::Idle;
    
    _clearColor = ImVec4(0.5f, 0.5f, 0.50f, 1.00f);
    
    _posP1 = ImVec2(100, 300);
    _posP2 = ImVec2(300, 300);
}

void DemoApp2::onUpdate(double delta)
{
    
    handleInput(delta);
    
    
     if(AppState::WaitClient == _state) {
         onUpdateWaitClient(delta);
     } else if(AppState::Connected == _state) {
         onUpdateConnected(delta);
     } else if(AppState::Test == _state) {
         updateBullets(delta);
         checkBulletHit();
     }

    drawGui();
    
    // drawShapes();
    
    drawPlayer(_player1, ColorRed);
    drawPlayer(_player2, ColorYellow);
    drawAllBullets();
    
    _pSystem.onUpdate(delta);
}




void DemoApp2::drawGuiIdle()
{
    if (ImGui::Button("Create Room (Host)")) {
        //std::cout << "'Button A' is clicked\n";
        onStartRoomClicked();
    }
    
    if (ImGui::Button("Join Room (Client)")) {
        //std::cout << "'Button A' is clicked\n";
        _errorMsg.set("");
        _state = DemoApp2::AppState::JoinHost; //AppState::JoinHost;
    }
    
    if (ImGui::Button("Go to Test")) {
        //std::cout << "'Button A' is clicked\n";
        _errorMsg.set("");
        _isHost = true;
        _state = DemoApp2::AppState::Test; //AppState::JoinHost;
    }
}


void DemoApp2::onCreateRoomClicked()
{
    setupHost();
    
     if(_isBindPortSuccess == false){
         return;
     }
    
     _state = AppState::WaitClient;
}

void DemoApp2::onStartRoomClicked()
{
    _state = AppState::CreateHost; //AppState::CreateHost;
}

void DemoApp2::onJoinHostClicked()
{
    setupClient();
    
}

void DemoApp2::drawGuiHost()
{
    ImGui::Text("Waiting client to join");
    ImGui::Text("Host location: locahost:%d", _port);
    
    
}

bool DemoApp2::setupSockAddress(SNString &str, int port)
{
    std::vector<SNString> tokens;
    
    str.split(tokens, ".");
    
    if(tokens.size() != 4) {
        _errorMsg.set("Invalid IP Address");
        return false;
    }
    _sockAddr.setIPv4(tokens[0].toInt(),
                      tokens[1].toInt(),
                      tokens[2].toInt(),
                      tokens[3].toInt());
    _sockAddr.setPort(port);
    
    _errorMsg.set("");
    return true;
}


void DemoApp2::drawGuiCreateHost()
{
    static char address[128] = "127.0.0.1";
    static int port = kPort;
    
    ImGui::Text("Define the port and Click Start Host");
    
   
    ImGui::InputInt("PORT", &port);
              
    if(_errorMsg.str() != "") {
        ImGui::Text("%s", _errorMsg.c_str());
    }
    
    if (ImGui::Button("Create Room")) {
        std::cout << "'Join Host' is clicked\n";
        std::cout << "ip: " << address << " port: " << port << "\n";
        _port = port;
        
        onCreateRoomClicked();
    }
    
}

void DemoApp2::drawGuiTest()
{
    
    ImGui::Text("Testing");

    fmt::memory_buffer out;
    format_to(out, "Player 1: {}  Player 2: {}",
                    _player1.score, _player2.score);
    ImGui::Text("%s", out.data());
    //fmt
    
    
    if (ImGui::Button("Back to main")) {
        //std::cout << "'Button A' is clicked\n";
        _errorMsg.set("");
        _state = DemoApp2::AppState::Idle; //AppState::JoinHost;
    }
    
    if (ImGui::Button("Host")) {
        _isHost = true;
    }

    if (ImGui::Button("Client")) {
        _isHost = false;
    }
    
    if (ImGui::Button("Add Host Button")) {
        //addBullet(0, 222, 222, 500, 0);
        addBulletAtPos(0, 222, 222, Dir::Down);
    }
    
    if (ImGui::Button("Add Client Button")) {
        addBulletAtPos(1, 422, 222, Dir::Left);
        //addBullet(1, 444, 111, 0, 500);
    }
    
    if (ImGui::Button("Hit Player 0")) {
        hitPlayer(0);
        //addBullet(1, 444, 111, 0, 500);
    }
    
    if (ImGui::Button("Hit Player 1")) {
        hitPlayer(1);
    }
    
    if (ImGui::Button("Remove Bullet")) {
        removeBullet(0, _bulletID-5);
    }

    if (ImGui::Button("Check Hit")) {
        checkBulletHit();
    }
    
    drawPlayer(_player1, ColorRed);
    drawPlayer(_player2, ColorYellow);
    drawAllBullets();
    
    
}

void DemoApp2::drawGuiClient()
{
    static char address[128] = "127.0.0.1";
    static int port = kPort;
    
    ImGui::Text("Enter the location to join");
    
    
//    IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    ImGui::InputText("IP", address, 128);    
    ImGui::InputInt("PORT", &port);
               
    
    if (ImGui::Button("Join Host")) {
        std::cout << "'Join Host' is clicked\n";
        std::cout << "ip: " << address << " port: " << port << "\n";
        
        SNString str = SNString(address);
        if(setupSockAddress(str, port)) {
            onJoinHostClicked();
            return;
        }
    }
    
    if(! _errorMsg.isEmpty()) {
        ImGui::Text("%s", _errorMsg.c_str());
      
    }
}

void DemoApp2::drawGuiConnected()
{
    ImGui::Text("Players are connected");
    ImGui::Text(_isHost ? "You are the host" : "You are the guest");
    ImGui::Text("Player 1 >> Score: %d  Pos: (%d, %d)",
                _player1.score, _player1.x, _player1.y);
    ImGui::Text("Player 2 >> Score: %d  Pos: (%d, %d)",
                _player2.score, _player2.x, _player2.y);
}


void DemoApp2::drawGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    
    if(AppState::Idle == _state) {
        drawGuiIdle();
    } else if(AppState::WaitClient == _state) {
        drawGuiHost();
    } else if(AppState::JoinHost == _state) {
        drawGuiClient();
    } else if(AppState::Connected == _state) {
        drawGuiConnected();
    } else if(AppState::CreateHost == _state) {
        drawGuiCreateHost();
    } else if(AppState::Test == _state) {
        drawGuiTest();
    }
    
    ImGui::End();
}

void DemoApp2::movePlayer(i8 pid, ImVec2 change, Dir dir, bool sendCmd)
{
    //ImVec2 &pos = (pid == 0) ? _posP1 : _posP2;
    int deltaX = (int) change.x;
    int deltaY = (int) change.y;
    
    Player& player = (pid == 0) ? _player1 : _player2;
    player.x += deltaX;
    player.y += deltaY;
    player.dir = dir;
    
    
    if(sendCmd) {
        sendMoveCommand(deltaX, deltaY, dir);
    }
}

void DemoApp2::handleInput(double deltaTime)
{
    if(AppState::Connected != _state && AppState::Test != _state) {
        return;
    }
    
    ImVec2 dir {0,0};
    float speed = 200;
    Dir playDir = Dir::None;
    
    
    
    Player &player = _isHost ? _player1 : _player2;
    int pid = player._id;

    if (getInputKey(SDLK_UP))    { dir.y -= 1; playDir = Dir::Up; }
    if (getInputKey(SDLK_DOWN))  { dir.y += 1; playDir = Dir::Down; }
    if (getInputKey(SDLK_LEFT))  { dir.x -= 1; playDir = Dir::Left; }
    if (getInputKey(SDLK_RIGHT)) { dir.x += 1; playDir = Dir::Right; }

    
    if (getInputKey(SDLK_a))  {
        //LOG("DEBUG: A is pressed!");
        fireBullet(player, deltaTime);
    }
    //
    
    
    if(dir.x == 0 && dir.y == 0) {
        return;
    }
    
    ImVec2 change;
    
    change.x = dir.x * deltaTime * speed;
    change.y = dir.y * deltaTime * speed;
    
    movePlayer(pid, change, playDir, shouldSendCmd(pid));
}

void DemoApp2::setupHost()
{
     bool isSuccess = _host.bindPort(_port);
    
     if(isSuccess == false) {
         _errorMsg.set("Fail to bind the port");
         _isBindPortSuccess = false;
         return;
     }
    
     _isHost = true;
     _isBindPortSuccess = true;
}

void DemoApp2::setupClient()
{
    // _isHost = false;
    
     try {
         _client.connectServer(_sockAddr);
        
         _state = AppState::Connected;
     }catch(...) {
         _errorMsg.set("Fail to connect the server");
         std::cout << "Fail to connect the server. err: " << errno << "\n";
     }
}

void DemoApp2::onConnected()
{
    _state = AppState::Connected;
    _cmdCounter = 0;
    _bulletID = 1;
    _currentPid = _isHost ? 0 : 1;
}

void DemoApp2::onUpdateWaitClient(double delta)
{
    
    if(_isBindPortSuccess == false) {
        return;
    }
    // log("Checking Network");
    _host.checkNetwork();   // ken: will callback onConnect if client connected
}

void DemoApp2::onUpdateConnected(double delta)
{
    updateBullets(delta);
    checkBulletHit();
    
     if(_isHost) {
         _host.sendDataOut();
         _host.checkNetwork();
     } else {
         _client.sendDataOut();
         _client.checkNetwork();
     }
}

void DemoApp2::sendMoveCommand(int deltaX, int deltaY, Dir dir)
{
    
    
    D2MovePacket packet;
    
    packet.playerID = _currentPid;
    packet.x = deltaX;
    packet.y = deltaY;
    packet.dir = enumInt(dir);
    
    if(_isHost) {
        _host.sendPacket(packet);
    } else {
        _client.sendPacket(packet);
    }
}

void DemoApp2::sendPlayerHitCommand(i8 pid)
{
    D2PlayerHitPacket packet;
    packet.playerID = pid;
    
    if(_isHost) {
        _host.sendPacket(packet);
    } else {
        _client.sendPacket(packet);
    }
}

void DemoApp2::sendRemoveBulletCommand(i8 pid, i32 bulletID)
{
    D2RemoveBulletPacket packet;
    packet.playerID = pid;
    packet.bulletID = bulletID;
    LOG("Send RemoveBullet: %s", packet.toString().c_str());
    
    if(_isHost) {
        _host.sendPacket(packet);
    } else {
        _client.sendPacket(packet);
    }
}



void DemoApp2::sendBulletCommand(const Bullet &bullet)
{
    
    
    D2BulletPacket packet;
    
    packet.playerID = bullet.pid;
    packet._id = bullet._id;
    packet.x = bullet.x;
    packet.y = bullet.y;
    packet.speedX = bullet.speedX;
    packet.speedY = bullet.speedY;
    
    if(_isHost) {
        _host.sendPacket(packet);
    } else {
        _client.sendPacket(packet);
    }
}



// Bullet
void DemoApp2::fireBullet(const Player &player, double delta)
{
    if(_fireCooldown > 0) {
        return; // not yet fire
    }
    
    addBulletAtPos(player._id, player.x, player.y, player.dir);
    

    _fireCooldown = 0.5;  // 1 sec
//
}

bool DemoApp2::shouldSendCmd(int pid)
{
    if(AppState::Test == _state) {
        return false;
    }
    
    if(_isHost) {
        return pid == 0;
    } else {
        return pid == 1;
    }
}

void DemoApp2::addBulletAtPos(int pid, int x, int y, Dir dir)
{
    int offsetValue = 10;
    int speedValue = kBulletSpeed;
    
    ImVec2 offset;
    ImVec2 speed;
    switch (dir) {
        case Dir::Up    : offset.y = -offsetValue; speed.y = -speedValue; break;
        case Dir::Down  : offset.y = offsetValue; speed.y = speedValue; break;
        case Dir::Left  : offset.x = -offsetValue; speed.x = -speedValue; break;
        case Dir::Right : offset.x = offsetValue; speed.x = speedValue; break;
        default:
            break;
    }
    
    
    addBullet(pid, x + offset.x, y + offset.y, speed.x, speed.y, shouldSendCmd(pid));
}

void DemoApp2::addBulletFromNet(i8 pid, i32 bulletID,
                                int x, int y, int speedX, int speedY)
{
    Bullet bullet;
    bullet.pid = pid;
    bullet._id = bulletID;
    bullet.x = x;
    bullet.y = y;
    bullet.speedX = speedX;
    bullet.speedY = speedY;
    bullet.isRemote = true;
    bullet.isDeleted = false;
    

    _bulletList.push_back(bullet);
    
}

void DemoApp2::addBullet(int pid, int x, int y,
                        int speedX, int speedY, bool sendToNet)
{
    Bullet bullet;
    bullet.pid = pid;
    bullet.x = x;
    bullet.y = y;
    bullet.speedX = speedX;
    bullet.speedY = speedY;
    bullet.isRemote = false;
    bullet.isDeleted = false;
    
    bullet._id = _bulletID++;

    _bulletList.push_back(bullet);
    
    if(sendToNet) {
        sendBulletCommand(bullet);
    }
}

void DemoApp2::updateBullets(double delta)
{
    //LOG("Debug updateBullets");
    for(Bullet &bullet : _bulletList) {
        int deltaX = (int)(delta * bullet.speedX);
        //fmt::print("DEBUG: deltaX={} speed={} delta={}\n", deltaX, bullet.speedX, delta);
        bullet.x += deltaX;
        bullet.y += (int)(delta * bullet.speedY);
    }
    
    _fireCooldown -= delta;

}

void DemoApp2::drawAllBullets()
{
    for(Bullet &bullet : _bulletList) {
        if(bullet.isDeleted) {
            continue;
        }
        drawBullet(bullet);
    }
}

void DemoApp2::drawBullet(const Bullet &bullet)
{
    ImColor color = bullet.pid == 0 ? ColorRed : ColorYellow;
    //LOG("drawBullet!!");
    auto pos = ImVec2(bullet.x, bullet.y);
    SNShapeHelper::drawCircleAtCenter(pos, kBulletRadius, color);
}

#pragma mark - Hit handling
void DemoApp2::hitPlayer(i8 pid)
{
    //LOG("hitPlayer");
    // fmt::print("HitPlayer {}\n", pid);
    
    auto & player = pid == 0 ? _player1 : _player2;
    player.score++;
    
    
    createHitParticle(ImVec2(player.x, player.y));
    
    if(pid == 0) {
        player.x = kP1BornPos.x;
        player.y = kP1BornPos.y;
    } else {
        player.x = kP2BornPos.x;
        player.y = kP2BornPos.y;
    }
}

void DemoApp2::removeBullet(i8 pid, i32 bulletID)
{
    //SNVector<Bullet> _bulletList;
    LOG("removeBullet: pid=%d bulletID=%ld", pid, bulletID);
    auto it = _bulletList.begin();
    for(;it != _bulletList.end();) {
        LOG("removeBullet: check [%d , %ld]", it->pid, it->_id);
        if(it->pid == pid && it->_id == bulletID) {
            LOG("RemoveBullet: found the instance!!");
            _bulletList.erase(it);
            break;
        } else {
            it++;
        }
    }
}

void DemoApp2::checkBulletHit()
{
    auto &otherPlayer = _currentPid == 0 ? _player2 : _player1;
    
    //float radius2 = kB
    //LOG("otherPlayerID=%d", otherPlayer._id);
    
    // only check the player on this side
    auto it = _bulletList.begin();
    
    auto hitBulletIter =_bulletList.end();
    
    for(;it != _bulletList.end(); it++) {
        auto bullet = *it;
        
        //LOG("bulletID=%d otherPlayerID=%d", bullet.pid, otherPlayer._id);
        if(bullet.pid == otherPlayer._id) {     // ignore my bullet
            continue;
        }
        
        if(bullet.isRemote) {
            continue;
        }
        
        float dist = square(bullet.x - otherPlayer.x)
                        + square(bullet.y - otherPlayer.y);
        //LOG("dist=%f check=%f", dist, kCheckHitSqr);
        if(dist < kCheckHitSqr){
            hitBulletIter = it;
            break;
        }
    }
    
    if(hitBulletIter == _bulletList.end()) {
        return; // No Hit Bullet
    }
    
    Bullet hitBullet = *hitBulletIter;
    handleBulletHit(otherPlayer._id, hitBullet._id);
    
    _bulletList.erase(hitBulletIter);
    sendRemoveBulletCommand(hitBullet.pid, hitBullet._id);
}

void DemoApp2::handleBulletHit(i8 pid, i32 bulletID)
{
    hitPlayer(pid);
    
    sendPlayerHitCommand(pid);
    // sendRemoveBulletCommand
}

