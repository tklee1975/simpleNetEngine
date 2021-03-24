//
//  TestNetSession.h
//  test_main
//
//  Created by kenlee on 11/3/2021.
//

#ifndef TestNetSession_h
#define TestNetSession_h

#include <stdio.h>
#include <simpleNet/NetEngine.h>

using namespace simpleNet;





class TestEchoClientSession : public SNSession {
public:
    TestEchoClientSession(SNSocket *);
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead);
    virtual void onConnect();
};

class TestEchoClientSessionFactory : public SNSessionFactory {
public:
   
    virtual SNSession *create(SNSocket *socket) {
        return new TestEchoClientSession(socket);
    }
};



// ---------



class SampleNetSession : public SNSession {
public:
    SampleNetSession(SNSocket *);
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead);
    virtual void onConnect();
    virtual void onDisconnect();
    
private:
    int _counter;
};

class SampleNetClientSession : public SNSession {
public:
    SampleNetClientSession(SNSocket *);
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead);
    virtual void onConnect();
    virtual void onDisconnect();
    
private:
    int _counter;
};

class SampleNetSessionFactory : public SNSessionFactory {
public:
    SampleNetSessionFactory(bool isHost) : SNSessionFactory() {
        _isHost = isHost;
    }
    
    virtual SNSession *create(SNSocket *socket) {
        if(_isHost) {
            return new SampleNetSession(socket);
        } else {
            return new SampleNetClientSession(socket);
        }
    }
private:
    bool _isHost;

};


#endif /* TestNetSession_h */
