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
#include "TestNetSession.h"
#include <fcntl.h> /* Added for the nonblocking socket */


using namespace simpleNet;
using namespace std;

//startsWith(const char *prefix);
void testStartsWith() {
    log("testStartsWith");
    
    std::vector<SNString> testList;
    testList.push_back(SNString("12"));
    testList.push_back(SNString("hello"));
    testList.push_back(SNString("-12"));
    
    SNString testStr = SNString("hello ABCDEF");
    
    for(int i=0; i<testList.size(); i++) {
        const char *prefix = testList[i].c_str();
        bool isOkay = testStr.startsWith(prefix);
        
        cout << "prefix=[" << prefix << "] okay=" << isOkay << "\n";
    }
    
    //std::string =
}


void testStringToInt() {
    log("testStringToInt");
    
    std::vector<SNString> testList;
    testList.push_back(SNString("12"));
    testList.push_back(SNString("aaa"));
    testList.push_back(SNString("-12"));
    
    for(int i=0; i<testList.size(); i++) {
        int result = testList[i].toInt();
        
        cout << "str=[" << testList[i].str() << "] int=" << result << "\n";
    }
    
    //std::string = 
}

void testTrimStr() {
    log("testTrimStr");

    SNString input = SNString("testing\n");
    
    cout << "Before Trim: [" << input.str() << "]\n";
    
    input.rtrim();
    
    cout << "After Trim: [" << input.str() << "]\n";
}

void testSplitStr() {
    log("TestSplitStr");
    
    const char *testStr = "mov 12 13";
    SNString str = SNString(testStr);
    
    std::vector<SNString> tokens = str.split(" ");
    
    for(int i=0; i<tokens.size(); i++) {
        SNString str = tokens[i];
        
        cout << i << ": " << str.str() << "\n";
    }
}

void testSampleClientSession()
{
    
    SNClient client = simpleNet::SNClient();
    
    
    client.setSessionFactory(new SampleNetSessionFactory(false));
    
    SNSocketAddr addr;
    addr.setIPv4(127, 0, 0, 1);
    addr.setPort(5433);

    bool isSuccess = client.connectServer(addr);
    
    if(isSuccess == false) {
        std::cout << "Fail to connect the server\n";
        return;
    }

    int counter = 0;
    std::cout << "Starting the Network Loop\n";
    for(;;) {
        client.checkNetwork();
        counter++;

        if((counter % 500000) == 0) {
            SNSession *session = client.getSession();
            if(session != NULL) {
                session->sendString("Client: tick passed\n");
            }
            //host.getSession()->sendString("100 tick passed");
            //sendString("100 tick passed");
        }
        //sleep(1);
    }
    
}



void testSampleHostSession() 
{
    
    SNHost host = simpleNet::SNHost();
    
    
    host.setSessionFactory(new SampleNetSessionFactory(true));
    
    
    bool isSuccess = host.bindPort(5433);
    if(isSuccess == false) {
        std::cout << "Fail to bind the port\n";
        return;
    }
    
    int counter = 0;
    std::cout << "Starting the Network Loop\n";
    for(;;) {
        host.checkNetwork();
        counter++;
        
        if((counter % 1000000) == 0) {
            SNSession *session = host.getSession();
            if(session != NULL) {
                session->sendString("100 tick passed\n");
            }
            //host.getSession()->sendString("100 tick passed");
            //sendString("100 tick passed");
        }
        //sleep(1);
    }
    
}


void testClientWithSession() {
    SNSocket sock;

    sock.createTCP();
    SNSocketAddr addr;
    addr.setIPv4(127, 0, 0, 1);
    addr.setPort(2345);

    sock.connect(addr);
    
    auto factory = TestEchoClientSessionFactory();
    SNSession *session = factory.create(&sock);

    session->setConnected(/* isHost */ false);
    
    
//    sock.send_c_str("GET /index.html HTTP/1.1\r\n"
//                        "Host: www.gov.hk\r\n"
//                        "\r\n");
    
    std::vector<char> buf;
    for(;;) {
        if(session->isAlive() == false) {
            break;
        }
        session->receiveData();  // ken: sleep inside if no data received
    }
}

void testCin() {
    std::cout << "Please input a string\n";
    std::string input;
    
    std::cin >> input;
    
    std::cout << "Your input: " << input << "\n";
}


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

// https://man7.org/linux/man-pages/man2/fcntl.2.html
//  fcnctl = File Control
//
void setNonblock(int socket)
{
    int flags;
    flags = fcntl(socket ,F_GETFL,0);   // F_GETFL =  Get the file access mode
                                        //           and the file status flags;
    assert(flags != -1);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);     // Set the mode to nonBlock
}
// Reference:
//  https://stackoverflow.com/questions/6714425/simple-socket-non-blocking-i-o/6714551
//  http://www.cs.tau.ac.il/~eddiea/samples/Non-Blocking/tcp-nonblocking-server.c.html
//  http://beej.us/guide/bgnet/
//  https://luminousmen.com/post/asynchronous-programming-blocking-and-non-blocking
void testNonBlockingServer() {
    SNSocketAddr addr;
    addr.setIPv4(0,0,0,0);
    addr.setPort(3458);
    
    std::cout << "Testing NonBlocking Server\n";

    SNSocket serverSocket;
    serverSocket.createTCP();
    
    serverSocket.setNonBlock(true);
    
    std::cout << "Start Bind\n";
    if(serverSocket.bind(addr) == false) {
        std::cout << "Fail to bind\n";
        return;
    }
    std::cout << "Done Bind\n";
    
    
    std::cout << "Start Listen\n";
    if(serverSocket.listen(10) == false) {
        std::cout << "Fail to listen\n";
        return;
    }
    std::cout << "Done Listen\n";
    
    SNSocket clientSocket;
    auto factory = SNEchoSessionFactory();
    
    
    std::cout << "Before Accept\n";
    for(;;) {
        SNSocketAcceptStatus result = serverSocket.attempAccept(clientSocket);
        if(result == SNSocketAcceptFail) {// No pending
            std::cout << "Client fail to accept\n";
            return;
        }
        
        if(result == SNSocketAcceptSuccess) {// No pending
            break;
        }
    
        std::cout << "Waiting Connection\n";
        sleep(1);
    }
    std::cout << "After Accept\n";
    
    
    // setNonblock(clientSocket.getSockFd());
    std::cout << "Client success to accept\n";
    
    SNSession *session = factory.create(&clientSocket);
        
    std::vector<char> buf;
    std::vector<char> outBuf;
    for(;;) {
        if(session->isAlive() == false) {
            break;
        }
        std::cout << "Before Receiver Data\n";
        session->receiveData();  // ken: sleep inside if no data received
        std::cout << "After Receiver Data\n";
    }
    
    
    serverSocket.close();
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
    
    SNEchoSession session = SNEchoSession(&clientSocket);
        
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
    
    // testCin();
    // testIMGUI();             // ken: not ready
    testStartsWith();
    // testStringToInt();
    // testTrimStr();
    // testSplitStr();
    // testSampleClientSession();
    // testSampleHostSession();
    // testNonBlockingServer();
    // testClientWithSession();
    // testClient();
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
