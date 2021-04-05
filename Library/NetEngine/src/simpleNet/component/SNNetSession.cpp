//
//  SNNetSession.cpp
//  net_engine_test
//
//  Created by kenlee on 3/4/2021.
//

#include "SNNetSession.h"

//SNNetSession(SNSocket &&sock);
//protected:
//virtual void onRecvFromSocket() override;
//                                    // ken: new implementation for packet
//
//void onRecvPacket(const SNVector<u8> &packetBuffer);
//bool recvPacketHeader(SNPacketHeader &header);
//bool sendPacketBuffer(u32 cmd, const SNVector<u8> &packetBuffer);
//bool recvPacket(size_t requiredSize);

namespace simpleNet {
SNNetSession::SNNetSession(SNSocket &&sock)
    : SNSession(std::move(sock))
{
    
}


void SNNetSession::onConnect() 
{
    _waitForContent = false;
}


bool SNNetSession::sendPacketHeader(u16 len, u32 cmd)
{
    SNPacketHeader header;
    header.len = len;        // 0a
    header.cmd = cmd;
    
    SNVector<u8> buffer;
    SNBinSerializer se(buffer);
    
    header.io(se);

    //SN_DUMP_HEX(buffer);
    int ret = _mySocket.send(buffer.data(), buffer.size());
    if(ret <= 0) {
        return false;
    }
    
    return ret == buffer.size();
}


bool SNNetSession::recvPacketHeader(SNPacketHeader &header)
{
    int headerLen = header.getDataLength();
    
    int ret = _mySocket.recv(_recvBuffer, headerLen, MSG_PEEK);
    if(ret < headerLen) { // ken: not enough packets, wait for more
        return false;
    }
    
    // Load the header packet data (socket buffer to my buffer)
    _recvBuffer.clear();
    int recvSize = _mySocket.recv(_recvBuffer, headerLen);
    _recvBuffer.resize(headerLen);
    //std::cout << "RecvSize: " << recvSize << " headerLen: " << headerLen << "\n";
    
    // Deserialize
    SNBinDeserializer de(_recvBuffer);
    header.io(de);
    
    
    LOG("header received: %s", header.toString().c_str());
    
    return true;
}

bool SNNetSession::recvPacket(SNPacketHeader::Cmd cmd, size_t requiredSize)
{
    int ret = _mySocket.recv(_recvBuffer, requiredSize, MSG_PEEK);
    if(ret < requiredSize) { // ken: not enough packets, wait for more
        return false;
    }
    
    _recvBuffer.clear();
    int recvSize = _mySocket.recv(_recvBuffer, requiredSize);
    _recvBuffer.resize(requiredSize);
    
    LOG("Recv Buffer: $d/%d byte received", recvSize, requiredSize);
    
    onRecvPacketBuffer(cmd, _recvBuffer);
    
    return true;
}

void SNNetSession::packetRecvLogic()
{
    //LOG("packetRecvLogic");
    const size_t maxPacketPerFrame = 100;
    for (size_t i=0; i<maxPacketPerFrame; i++) {
        size_t nRead = _mySocket.availableBytesToRead();
        if(nRead <= 0) {    // ken: nRead = 0 if not data retrieved at the moment
            break;  //
        }
        
        SNPacketHeader header;
        if(_waitForContent == false) {
            
            if(recvPacketHeader(header) == false) {
                continue;
            }
            
            //LOG("** recvPack: cmd=%d len=%d", header.cmd, header.len);
            _waitForContent = header.len > 0 ? true : false;
            _packetContentSize = header.len;
            _packetCmd = header.cmd;
        } else {
            //LOG("recvPack: cmd=%d len=%d", header.cmd, header.len);
            if(recvPacket(_packetCmd, _packetContentSize) == false) {
                continue;
            }
            LOG("packet received");
            // onRecvPacketBuffer(_recvBuffer);
            
            // Reset
            _waitForContent = false;
            _packetContentSize = 0;
        }
        
    }
}

void SNNetSession::onRecvFromSocket()
{
    packetRecvLogic();
}

bool SNNetSession::sendPacketBuffer(SNPacket &packet)
{
    _sendBuffer.clear();
    //packet.to
    packet.toBuffer(_sendBuffer);
    
    // Sending the package
    return sendPacketBuffer(packet.cmd, _sendBuffer);
}

bool SNNetSession::sendPacketBuffer(
        u32 cmd, const SNVector<u8> &packetBuffer)
{
    u16 len = static_cast<u16>(packetBuffer.size());
    sendPacketHeader(len, cmd);
    LOG("sendPacketData: cmd=%d len=%d", cmd, len);
    int ret = _mySocket.send(packetBuffer.data(), (size_t) len);
    
    if(ret <= 0) {
        return false;
    }
    
    return ret < packetBuffer.size();
}




}
