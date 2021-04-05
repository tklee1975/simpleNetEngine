//
//  TestPackageSession.hpp
//  net_engine_test
//
//  Created by kenlee on 2/4/2021.
//

#ifndef TestPackageSession_hpp
#define TestPackageSession_hpp

#include <memory>
#include <simpleNet/NetEngine.h>
#include <simpleNet/CoreLib.h>
using namespace simpleNet;



class TestPacketServerSession : public SNNetSession
{
public:
    TestPacketServerSession(SNSocket &&sock);
    
    virtual void onRecvPacketBuffer(const SNPacketHeader::Cmd &cmd,
                                    const SNVector<u8> &packetBuffer) override;
//
//    virtual void onRecvFromSocket() override;
//
//    void onRecvPacket(const SNVector<u8> &packetBuffer);
    
protected:
//    bool recvPacketHeader(SNPacketHeader &header);
//    bool recvPacket(size_t requiredSize);
    
private:
//    SNVector<u8> _recvBuffer;
//    SNVector<u8> _sendBuffer;
//    bool _waitForContent = false;
//    size_t _packetContentSize = 0;
//    
//    void simpleRecvLogic(SNSocket &socket);
//    void packetRecvLogic(SNSocket &socket);
};

class TestPacketClientSession : public SNNetSession
{
public:
    TestPacketClientSession(SNSocket &&sock);
    
    virtual void onUpdate() override;
    virtual void onRecvPacketBuffer(const SNPacketHeader::Cmd &cmd,
                                    const SNVector<u8> &packetBuffer) override;
    
//    virtual void onRecvFromSocket() override;
//    virtual void onConnect() override;
//    virtual void onUpdate() override;
//
//    void sendPacket(u32 cmd);
//    void sendPacketBuffer(u32 cmd, const SNVector<u8> &packetBuffer);
    
private:
//    SNVector<u8> _recvBuffer;
    SNVector<u8> _sendBuffer;
    u32 counter = 1;
    
///    void sendPacketHeader(u16 len, u32 cmd);
    
};



class TestPacketSessionFactory : public SNSessionFactory {
public:
    TestPacketSessionFactory(bool isServer)
            : SNSessionFactory(),
            _isServer(isServer) {}
    
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {
        if(_isServer) {
            return std::make_unique<TestPacketServerSession>(std::move(socket));
        } else {
            return std::make_unique<TestPacketClientSession>(std::move(socket));
            
        }
     }

private:
    bool _isServer;

};




#endif /* TestPackageSession_hpp */
