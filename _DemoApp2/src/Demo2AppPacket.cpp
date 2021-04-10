//
//  Demo2AppPacket.cpp
//  SimpleNet
//
//  Created by kenlee on 5/4/2021.
//

#include "Demo2AppPacket.h"
#include "DemoApp2.h"
#include <fmt/core.h>

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
    fmt::memory_buffer out;
    format_to(out, "bulletID={} pid={} x={} y={} speed={},{} dir={}",
                    _id, playerID, x, y, speedX, speedY, dir);
              
    return std::string(out.data());
}

#pragma mark - Remove Bullet
D2RemoveBulletPacket::D2RemoveBulletPacket()
: SNPacket()
{
    cmd = kCmdRemoveBullet;
}

void D2RemoveBulletPacket::fromBuffer(const SNVector<u8>& buf) {
    SNBinDeserializer de(buf);
    de.io(playerID);
    de.io(bulletID);
}

void D2RemoveBulletPacket::toBuffer(SNVector<u8>& buf) {
    SNBinSerializer se(buf);
    se.io(playerID);
    se.io(bulletID);
}

std::string D2RemoveBulletPacket::toString() {
    fmt::memory_buffer out;
    format_to(out, "removeBullet. pid={} bullet={}", playerID, bulletID);
    return std::string(out.data());
}


#pragma mark - PlayerHitPacket

D2PlayerHitPacket::D2PlayerHitPacket()
: SNPacket()
{
    cmd = kCmdPlayerHit;
}

void D2PlayerHitPacket::fromBuffer(const SNVector<u8>& buf) {
    SNBinDeserializer de(buf);
    
    de.io(playerID);
}

void D2PlayerHitPacket::toBuffer(SNVector<u8>& buf) {
    SNBinSerializer se(buf);
    
    se.io(playerID);
}

std::string D2PlayerHitPacket::toString() {
    fmt::memory_buffer out;
    format_to(out, "hitPlayer. pid={}", playerID);
    return std::string(out.data());
}

#pragma mark - MovePacket

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
    
    fmt::memory_buffer out;
    format_to(out, "pid={} x={} y={} dir={}", playerID, x, y, dir);
//
//
//              "bulletID={} pid={} x={} y={} speed={},{} dir={}",
//                    _id, playerID, x, y, speedX, speedY, dir);
              
    return std::string(out.data());
}

