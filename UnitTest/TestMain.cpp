//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <CoreLib.h>
#include <NetEngine.h>
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>
#include <fmt/core.h>
#include <session/SNEchoSession.h>

using namespace simpleNet;
using namespace std;

void testClient() {
    SNSocket sock;

	sock.createTCP();
    SNSocketAddr addr; 
    addr.setIPv4(127, 0, 0, 1);
    addr.setPort(1234);

    sock.connect(addr);
//	sock.send_c_str("GET /index.html HTTP/1.1\r\n"
//						"Host: www.gov.hk\r\n"
//						"\r\n");
    const char *msg = "Testing";
    sock.send(msg, strlen(msg));
    
	std::vector<char> buf;
	for(;;) {
		size_t n = sock.availableBytesToRead();
        if (n == 0) {
            //printf("wait..\n");
            simpleNet::sleep(1);
            continue;
        }

        sock.recv(buf, n);
        buf.push_back(0);
		printf("recv %d: %s\n", (int)n, buf.data());
		break;
	}
}

// ken: not working yet 
void testEastlVector() {
    std::cout << "Eastl Vector\n";
    eastl::fixed_vector<int, 25, true> intSet; // Create a set capable of holding 25 elements.
    //intSet.push_back(1);
    // for(int i=0; i<10; i++) {
    //     //intSet[i] = i * i;
    //     //intSet.push_back(1);
    //     intSet.push_back(1);
    // }
     
    // for(fixed_set<int>::iterator it = intSet.begin(), itEnd = intSet.end(); 
    //             it != itEnd; ++it) {
    //   fmt::print("fixed set: {}.\n", *it);  
    // }
    fmt::print("vectorSize: {}\n", intSet.size());

    //fmt::print("fixed set: {}.\n", intSet);
}

void testIMGUI() {
    cout << "Testing IMGUI\n";

    //ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);

}

void testSimpleString() {
    SNString str = SNString("Hello Str");
    
    cout << "str: " << str.str() << "\n";
    
    std::vector<char> vecBuf;
    
    str.copyTo(vecBuf);
    vecBuf.push_back('\0');
    
    cout << "vecBuf: " << vecBuf.data() << "\n";
}


void test() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3456);


}

void testEchoServer() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3456);

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
    auto factory = SNEchoSessionFactory();
    
    bool isAccepted = serverSocket.accept(clientSocket);
    if(isAccepted == false) {
        std::cout << "Client fail to accept\n";
        return;
    }
    std::cout << "Client success to accept\n";
    
    SNSession *session = factory.create(&clientSocket);
        
    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        if(session->isAlive() == false) {
            break;
        }
        session->receiveData();  // ken: sleep inside if no data received
    }
    
    
    serverSocket.close();
}



void testServerUsingSession() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3456);

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
    
    SNSession session = SNSession(&clientSocket);
        
    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        if(session.isAlive() == false) {
            break;
        }
        session.receiveData();  // ken: sleep inside if no data received
    }
    
    
    serverSocket.close();
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
    
    // testIMGUI();             // ken: not ready
    testClient();
    // testEchoServer();
    //testServerUsingSession();
    //testSimpleString();
    //testEastlVector();        // ken: not ready 
    //testSimpleEchoServer();
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
