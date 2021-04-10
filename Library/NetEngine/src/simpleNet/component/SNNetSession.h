//
//  SNNetSession.hpp
//  net_engine_test
//
//  Created by kenlee on 3/4/2021.
//

#ifndef SNNetSession_hpp
#define SNNetSession_hpp


#include <memory>
#include <simpleNet/NetEngine.h>
#include <simpleNet/CoreLib.h>
#include <simpleNet/component/SNPacket.h>


namespace simpleNet {

class SNNetSession : public SNSession
{
public:
    SNNetSession(SNSocket &&sock);
    
    bool sendPacketBuffer(SNPacket &packet);
    bool sendPacketBuffer(u32 cmd, const SNVector<u8> &packetBuffer);

    
    
protected:
    virtual void onRecvFromSocket() override;
                                        // ken: new implementation for packet
    virtual void onConnect() override;
    
    virtual void onRecvPacketBuffer(
            const SNPacketHeader::Cmd &cmd, const SNVector<u8> &packetBuffer) {}
    
    
    
    bool sendPacketHeader(u16 len, u32 cmd);
    
private:
    SNVector<u8> _recvBuffer;
    SNVector<u8> _sendBuffer;
    bool _waitForContent = false;
    size_t _packetContentSize = 0;
    SNPacketHeader::Cmd _packetCmd;

    bool recvPacketHeader(SNPacketHeader &header);
    bool recvPacket(SNPacketHeader::Cmd cmd, size_t requiredSize);
    void packetRecvLogic();
};

}

#endif /* SNNetSession_hpp */