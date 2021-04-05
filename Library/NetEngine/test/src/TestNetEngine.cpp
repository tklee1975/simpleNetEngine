//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <simpleNet/CoreLib.h>
#include <simpleNet/NetEngine.h>
#include <simpleNet/BinSerializer.h>
#include <simpleNet/BinDeserializer.h>
#include "TestPacketSession.h"
#include <simpleNet/session/SNTestPacket.h>


using namespace simpleNet;
using namespace std;

//SNTestPacket
template<class T>
void checkPacketSerialize(T &inPacket, T &outPacket,
                            SNVector<u8> &buffer) {
    inPacket.toBuffer(buffer);
    outPacket.fromBuffer(buffer);
}

void testSNTestPacket2()
{
    SNTestPacket srcPacket(100, 10);
    SNTestPacket outPacket;
    
    SNVector<u8> buffer;
    checkPacketSerialize(srcPacket, outPacket, buffer);
    
    
    std::cout << "source packet:\n[" << srcPacket.toString() << "]\n";
    std::cout << "deserialized packet:\n[" << outPacket.toString() << "]\n";
}

void testSNTestPacket()
{
    SNTestPacket packet(100, 10);
    
    std::cout << "source packet:\n[" << packet.toString() << "]\n";
    
    SNVector<u8> buffer;
    packet.toBuffer(buffer);
    
    SNTestPacket dePacket;
    dePacket.fromBuffer(buffer);
    
    std::cout << "deserialized packet:\n[" << packet.toString() << "]\n";
}

void testPacketClient() {
    SNClient client = simpleNet::SNClient();
    //SampleNetSessionFactory factory(true);
    
    client.setSessionFactory(make_shared<TestPacketSessionFactory>(false));
    
    
    SNSocketAddr addr;
    addr.setIPv4(127, 0, 0, 1);
    addr.setPort(5433);
    
    client.connectServer(addr);
    
    int counter = 1;
    for(;;) {
        std::cout << "Loop " << counter << "\n";
        //client.sendPa
        client.sendDataOut();
        client.checkNetwork();
        
        sleep(1);
        counter++;
    }
    
    //client.pa
}

//SNPacketHeader
void testPacketHeader()
{
    SNPacketHeader header;
    header.len = 10;
    header.cmd = 1;
    
    std::cout << "header: " << header.toString() << "\n";
    
    SNVector<u8> buffer;
    SNBinSerializer se(buffer);
    
    header.io(se);
    
    SN_DUMP_HEX(buffer);
    
    //
    SNBinDeserializer de(buffer);
    SNPacketHeader deHeader;    // deserialized header
    
    deHeader.io(de);
    
    std::cout << "Deserialized header: " << deHeader.toString() << "\n";
    
}

void testPacketServer() {
    SNHost host = simpleNet::SNHost();
    //SampleNetSessionFactory factory(true);
    
    host.setSessionFactory(make_shared<TestPacketSessionFactory>(true));
    
    
    bool isSuccess = host.bindPort(5433);
    if(isSuccess == false) {
        std::cout << "Fail to bind the port\n";
        return;
    }
    
    int counter = 0;
    std::cout << "Starting the Network Loop\n";
    for(;;) {
        //
        std::cout << "Server Loop " << counter << "\n";
        host.sendDataOut();
        host.checkNetwork();
        
        
        if(host.isConnectingClient()) {
            SNTestPacket packet(counter, 10);
            LOG("SNTestPacket: packet.cmd=%d", packet.cmd);
            host.sendPacket(packet);
        }
        //.sendPacket(packet);
        
        counter++;
        
       
        
        sleep(1);
    }
    

}

void test1() {
    std::cout << "Test Network Engine\n";
}

// For Single and Temp testing
void runSingleTest() {
    std::cout << "Run Single Test\n";
    
    //testSNTestPacket2();
    //testSNTestPacket();
    testPacketClient();   // test with PacketServer
    //testPacketHeader();
    //testPacketServer();     // test with PacketClient
    //test1();
    
    std::cout << "End of Single Test\n";
}

void runAllTest() {
    std::cout << "Run All Test\n";
    
    test1();
}

int main(int argc, char** argv) {
    printf("Running UnitTest: %d\n", argc);

    if(argc <= 1) {
        runSingleTest();
        return 0;
    }
    // std::cout << "Input: " <<  argv[1] << "\n";
    if(my_strcasecmp(argv[1], "all") == 0) {
        runAllTest();
    } else {
        runSingleTest();
    }

    return 0;
} 
