//
//  SimpleNetAppSession.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "DemoApp2Session.h"
#include "DemoApp2.h"
#include "Demo2AppPacket.h"

DemoApp2Session::DemoApp2Session(SNSocket && _sock, DemoApp2 &_app, bool _isHost)
    : SNNetSession(std::move(_sock))
    , mainApp(_app)
    , isHost(_isHost)
{
    
}

DemoApp2Session::~DemoApp2Session()
{
}

void DemoApp2Session::onConnect()
{
    std::cout << "Connected to client\n";
    
    mainApp.onConnected();
}

void DemoApp2Session::onDisconnect()
{
    std::cout << "Client disconnected\n";
}


void DemoApp2Session::onRecvPacketBuffer(const SNPacketHeader::Cmd &cmd,
                                         const SNVector<u8> &packetBuffer)
{
    
    std::cout << "CMD: " << cmd << " bufSize=" << packetBuffer.size() << "\n";
    SN_DUMP_HEX(packetBuffer);
    
    if(cmd == kCmdMove) {
        D2MovePacket packet;
        packet.fromBuffer(packetBuffer);
        
        ImVec2 change;
        change.x = packet.x;
        change.y = packet.y;
        
        mainApp.movePlayer(packet.playerID, change, (DemoApp2::Dir) packet.dir, false);
    } else if(cmd == kCmdBullet) {
        D2BulletPacket packet;
        packet.fromBuffer(packetBuffer);
        
        ImVec2 change;
        change.x = packet.x;
        change.y = packet.y;
        
        mainApp.addBulletFromNet(packet.playerID, packet._id,
                                  packet.x, packet.y,
                                    packet.speedX, packet.speedY);
    } else if(cmd == kCmdPlayerHit) {
        D2PlayerHitPacket packet;
        packet.fromBuffer(packetBuffer);
        
        mainApp.hitPlayer(packet.playerID);
        
    } else if(cmd == kCmdRemoveBullet) {
        D2RemoveBulletPacket packet;
        packet.fromBuffer(packetBuffer);
        LOG("RemoveBullet: %s", packet.toString().c_str());
        mainApp.removeBullet(packet.playerID, packet.bulletID);
    }
}
