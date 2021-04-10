//
//  Demo2AppPacket.hpp
//  SimpleNet
//
//  Created by kenlee on 5/4/2021.
//

#pragma once

#include <simpleNet/CoreLib.h>
#include <simpleNet/NetEngine.h>

using namespace simpleNet;

#pragma mark - Bullet
//
class D2BulletPacket : public SNPacket {
public:

    i32 _id = 0;
    i8 playerID = 0;
    i16 x = 0;
    i16 y = 0;
    i16 speedX = 0;
    i16 speedY = 0;
    i8 dir = 0;

    D2BulletPacket();

    virtual void fromBuffer(const SNVector<u8>& buf) override;
    virtual void toBuffer(SNVector<u8>& buf) override;
    std::string toString();
};

#pragma mark - Player Hit
class D2PlayerHitPacket : public SNPacket {
public:

    i8 playerID = 0;
   
    D2PlayerHitPacket();

    virtual void fromBuffer(const SNVector<u8>& buf) override;
    virtual void toBuffer(SNVector<u8>& buf) override;
    std::string toString();
};

#pragma mark - Remove Bullet
class D2RemoveBulletPacket : public SNPacket {
public:

    i8 playerID = 0;
    i32 bulletID = 0;
   
    D2RemoveBulletPacket();

    virtual void fromBuffer(const SNVector<u8>& buf) override;
    virtual void toBuffer(SNVector<u8>& buf) override;
    std::string toString();
};


#pragma mark - Player Move
class D2MovePacket : public SNPacket {
public:
    
    i8 playerID = 0;
    i16 x = 0;
    i16 y = 0;
    i8 dir = 0;
    
    D2MovePacket();
    
    virtual void fromBuffer(const SNVector<u8>& buf) override;
    virtual void toBuffer(SNVector<u8>& buf) override;
    std::string toString();
};
