//
//  Demo2AppPacket.cpp
//  SimpleNet
//
//  Created by kenlee on 5/4/2021.
//

#include "Demo2AppPacket.h"
#include "DemoApp2.h"

using namespace simpleNet;

// --- Bullet Packet ---
D2BulletPacket::D2BulletPacket()
: SNPacket()
{
    cmd = kCmdBullet;
}


void D2BulletPacket::fromBuffer(const SNVector<u8>& buf)
{
    SNBinDeserializer de(buf);
    
    de.io(_id);
    de.io(playerID);
    de.io(x);
    de.io(y);
    de.io(speedX);
    de.io(speedY);
    de.io(dir);
}

void D2BulletPacket::toBuffer(SNVector<u8>& buf)
{
    
    SNBinSerializer se(buf);
    se.io(_id);
    se.io(playerID);
    se.io(x);
    se.io(y);
    se.io(speedX);
    se.io(speedY);
    se.io(dir);
}

std::string D2BulletPacket::toString()
{
    std::string result;
    char temp[100];
    
    sprintf(temp, "bulletID=%d pid=%d x=%d y=%d speed=%d,%d dir=%d",
                    _id, playerID, x, y, speedX, speedY, dir);
        
    
    return result;
}



// --- Move Packet ---

D2MovePacket::D2MovePacket()
: SNPacket()
{
    cmd = kCmdMove;
}

void D2MovePacket::fromBuffer(const SNVector<u8>& buf)
{
    SNBinDeserializer de(buf);
    
    de.io(playerID);
    de.io(x);
    de.io(y);
    de.io(dir);
}

void D2MovePacket::toBuffer(SNVector<u8>& buf)
{
    
    SNBinSerializer se(buf);
    se.io(playerID);
    se.io(x);
    se.io(y);
    se.io(dir);
}

std::string D2MovePacket::toString()
{
    std::string result;
    char temp[100];
    
    sprintf(temp, "pid=%d x=%d y=%d dir=%d", playerID, x, y, dir);
        
    
    return result;
}

