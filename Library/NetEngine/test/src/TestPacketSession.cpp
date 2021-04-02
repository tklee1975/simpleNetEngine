//
//  TestPackageSession.cpp
//  net_engine_test
//
//  Created by kenlee on 2/4/2021.
//

#include "TestPacketSession.h"
#include <simpleNet/session/SNTestPacket.h>

                         //TestPacketServerSession(SNSocket &&sock);
TestPacketServerSession::TestPacketServerSession(SNSocket &&sock)
    : SNNetSession(std::move(sock))
{
    
}
//
//void TestPacketServerSession::simpleRecvLogic(SNSocket &socket)
//{
//    size_t nRead = socket.availableBytesToRead();
//    if(nRead == 0) {    // ken: nRead = 0 if not data retrieved at the moment
//        //sleep(1);       // 1 second     //
//        return;
//    }
//    std::cout << "available to read " << nRead << "byte \n";
//
//    int len = 100;
//
//    int ret = socket.recv(_recvBuffer, len, MSG_PEEK);
//    std::cout << "return result ret=" << ret << " \n";
//    if(ret <= 0) {  // No data from socket
//        //LOG("onRecvFromSocket: neg ret. ret=%d", ret);
//        //onDisconnect();
//        return;
//    }
//    if(ret != len) {
//        return;
//    }
//
//
//    //_recvBuffer.
//    _recvBuffer.clear();
//    socket.recv(_recvBuffer, len);
//    _recvBuffer.resize(len);
//
//    SNString str;
//    SNStringUtil::binToHex(str, _recvBuffer);
//
//    str.append("\n\n");
//    sendString(str);
//
//    // SN_DUMP_HEX(_recvBuffer);
//}
//
//bool TestPacketServerSession::recvPacketHeader(SNPacketHeader &header)
//{
//    int headerLen = header.getDataLength();
//
//    int ret = _mySocket.recv(_recvBuffer, headerLen, MSG_PEEK);
//    if(ret < headerLen) { // ken: not enough packets, wait for more
//        return false;
//    }
//
//    // Load the header packet data (socket buffer to my buffer)
//    _recvBuffer.clear();
//    int recvSize = _mySocket.recv(_recvBuffer, headerLen);
//    _recvBuffer.resize(headerLen);
//    std::cout << "RecvSize: " << recvSize << " headerLen: " << headerLen << "\n";
//
//    // Deserialize
//    SNBinDeserializer de(_recvBuffer);
//    header.io(de);
//
//    return true;
//}
//
//bool TestPacketServerSession::recvPacket(size_t requiredSize)
//{
//    int ret = _mySocket.recv(_recvBuffer, requiredSize, MSG_PEEK);
//    if(ret < requiredSize) { // ken: not enough packets, wait for more
//        return false;
//    }
//
//    _recvBuffer.clear();
//    int recvSize = _mySocket.recv(_recvBuffer, requiredSize);
//    _recvBuffer.resize(requiredSize);
//
//    return true;
//}

void TestPacketServerSession::onRecvPacketBuffer(const SNVector<u8> &packetBuffer)
{
    SNTestPacket packet;    // TODO: ken: determine by header.cmd
    
    packet.fromBuffer(packetBuffer);
    
    // Packet Ready!!
    std::cout << "Packet Ready: " << packet.toString() << "\n";
    
}
//
//void TestPacketServerSession::packetRecvLogic(SNSocket &socket)
//{
//    const size_t maxPacketPerFrame = 100;
//    for (size_t i=0; i<maxPacketPerFrame; i++) {
//        size_t nRead = socket.availableBytesToRead();
//        if(nRead <= 0) {    // ken: nRead = 0 if not data retrieved at the moment
//            break;  // 
//        }
//        
//        if(_waitForContent == false) {
//            SNPacketHeader header;
//            if(recvPacketHeader(header) == false) {
//                continue;
//            }
//            _waitForContent = true;
//            _packetContentSize = header.len;
//        } else {
//            SNTestPacket packet;    // TODO: ken: determine by header.cmd
//            if(recvPacket(_packetContentSize) == false) {
//                continue;
//            }
//            
//            onRecvPacket(_recvBuffer);
//            
//            // Reset
//            _waitForContent = false;
//            _packetContentSize = 0;
//            
//            //packet.fromBuffer(<#const SNVector<u8> &buf#>)
//        }
//        
//        
//        LOG("Header Received!");
//        //SN_DUMP_HEX(_recvBuffer);
//        //std::cout << " ---> [" << header.toString() << "]\n";
//    }
//}
//
//void TestPacketServerSession::onRecvFromSocket()
//{
//    //simpleRecvLogic(_mySocket);
//    packetRecvLogic(_mySocket);
////    std::string strValue = std::string(_recvBuffer.begin(), _recvBuffer.end());
////    std::cout << "receiveData: " << strValue << "\n";
//    
//    
//}

// ----------------------
TestPacketClientSession::TestPacketClientSession(SNSocket &&sock)
    : SNNetSession(std::move(sock))
{
    
}
//
//void TestPacketClientSession::sendPacketHeader(u16 len, u32 cmd)
//{
//    SNPacketHeader header;
//    header.len = len;        // 0a
//    header.cmd = cmd;
//
//    SNVector<u8> buffer;
//    SNBinSerializer se(buffer);
//
//    header.io(se);
//
//    //SN_DUMP_HEX(buffer);
//    _mySocket.send(buffer.data(), buffer.size());
//}
//
//void TestPacketClientSession::sendPacketBuffer(
//        u32 cmd, const SNVector<u8> &packetBuffer)
//{
//    u16 len = static_cast<u16>(packetBuffer.size());
//    sendPacketHeader(len, cmd);
//    _mySocket.send(_sendBuffer.data(), (size_t) len);
//}

void TestPacketClientSession::onUpdate()
{
    std::cout << "onUpdate\n";
    //sendPacket(counter);
    
    // Packing the packer
    SNTestPacket packet(counter, 5);
    
    _sendBuffer.clear();
    packet.toBuffer(_sendBuffer);
    
    // Sending the package
    sendPacketBuffer(packet.cmd, _sendBuffer);
    
    
    counter++;
}
