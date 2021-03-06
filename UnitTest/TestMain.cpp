//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <CoreLib.h>
#include <NetEngine.h>
//#include <EASTL/fixed_set.h>

using namespace simpleNet;
using namespace std;

// ken: not working yet 
// void testEastlVector() {
//     std::cout << "Eastl Vector\n";
//     fixed_set<int, 25> intSet; // Create a set capable of holding 25 elements.
// }

void testSimpleString() {
    SNString str = SNString("Hello Str");
    
    cout << "str: " << str.str() << "\n";
    
    std::vector<char> vecBuf;
    
    str.copyTo(vecBuf);
    vecBuf.push_back('\0');
    
    cout << "vecBuf: " << vecBuf.data() << "\n";
}

//
// this is a simple Hello server
//  Run this and
//  use telnet 3000 to access it
//
void testSimpleEchoServer() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3000);

    SNSocket serverSocket;
    serverSocket.createTCP();
    if(serverSocket.bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return;
    }
    if(serverSocket.listen(10) == false) {
        std::cout << "Fail to listen\n";
        return;
    }
    
    SNSocket clientSocket;
    
    bool isAccepted = serverSocket.accept(clientSocket);
    if(isAccepted == false) {
        std::cout << "Client fail to accept\n";
        return;
    }
    std::cout << "Client success to accept\n";
        
    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        size_t n = clientSocket.availableBytesToRead();
        if(n <= 0) {
            sleep(1);
            continue;
        }
        
        clientSocket.recv(buf, n);
        buf.push_back(0);   // add the character '\0' to make it a string

        
        
        //std::cout << "Byte Read: " << ((int) n) << " input: " << buf << "\n";
        const char *msg = (const char *) buf.data();
        std::cout << " input: " << msg << "\n";

        SNString returnMsg = SNString("ECHO: ");
        returnMsg.append(msg);
        
        //outBuf = "ECHO: ";
        returnMsg.copyTo(outBuf);
        
        clientSocket.send(outBuf.data(), outBuf.size());
    }
    
    
    clientSocket.close();
    serverSocket.close();
   

}


//
// this is a simple Hello server
//  Run this and
//  use telnet 3000 to access it
//
void testSimpleHelloServer() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3000);

    SNSocket serverSocket;
    serverSocket.createTCP();
    if(serverSocket.bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return;
    }
    if(serverSocket.listen(10) == false) {
        std::cout << "Fail to listen\n";
        return;
    }
    
    SNSocket clientSocket;
    
    bool isAccepted = serverSocket.accept(clientSocket);
    if(isAccepted == false) {
        std::cout << "Client fail to accept\n";
        return;
    }
    std::cout << "Client success to accept\n";
        
    const char *msg = "Great! You can access the server!\n";
    clientSocket.send(msg, strlen(msg));
    
    clientSocket.close();
    serverSocket.close();
    
//    ret = ::listen(sock., 3);
//    if (ret < 0) {
//        //throw MyError("bind");
//        std::cout << "fail to listen\n";
//        return;
//    }
//    std::cout << "Listen Socket Okay\n";
   

}

void testTcpBind() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3000);

    SNSocket sock;
    sock.createTCP();
    sock.bind(addr);
    
    std::vector<char> buf;

    for(;;) {
        sock.recv(buf, 4);

        buf.push_back(0);
        printf("recv: %s\n", buf.data());
        simpleNet::sleep(1);
    }
}

void testSockAddr() {
    SNSocketAddr *addr = new SNSocketAddr();
    
    addr->setPort(123);
    cout << "Port: " << addr->port() << "\n";
    //fmt::print
}

void testLog() {
    simpleNet::log("testing: %d %d", 123, 2312);
}

void test1() {
    std::cout << "Test1\n";
}

// For Single and Temp testing
void runSingleTest() {
    std::cout << "Run Single Test\n";
    
    //testSimpleString();
    //testEastlVector();
    testSimpleEchoServer();
    // testSimpleHelloServer();
    // testTcpBind();
    // testSockAddr();
    // testLog();
    // test1();
    
    std::cout << "End of Single Test\n";
}

void runAllTest() {
    std::cout << "Run All Test\n";
    
    //testEastlVector();
    testTcpBind();
    testSockAddr();
    testLog();
    test1();
}

int main(int argc, char** argv) {
    printf("Running UnitTest: %d\n", argc);

    if(argc <= 1) {
        runSingleTest();
        return 0;
    }
    // std::cout << "Input: " <<  argv[1] << "\n";
    if(strcasecmp(argv[1], "all") == 0) {
        runAllTest();
    } else {
        runSingleTest();
    }

    return 0;
} 
