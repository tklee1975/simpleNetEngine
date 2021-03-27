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
#include <simpleNet/CoreLib.h>

using namespace simpleNet;





class TestHttpGetSession : public SNSession
{
public:
    TestHttpGetSession(SNSocket &&);
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
};


class TestEchoClientSession : public SNSession {
public:
    TestEchoClientSession(SNSocket *);
    TestEchoClientSession(SNSocket &&);
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
};

class TestEchoClientSessionFactory : public SNSessionFactory {
public:
   
//    virtual SNSession *create(SNSocket *socket) override {
//        return new TestEchoClientSession(socket);
//    }
//    
    
    
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {
        
        return std::make_unique<TestEchoClientSession>(std::move(socket));
    }
    
};



// ---------



class SampleNetSession : public SNSession
{
public:
    SampleNetSession(SNSocket &&sock);
    
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    
private:
    int _counter;
};

class SampleNetClientSession : public SNSession
{
public:
    SampleNetClientSession(SNSocket &&);
    
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    
private:
    int _counter;
};

class SampleNetSessionFactory : public SNSessionFactory {
public:
    SampleNetSessionFactory(bool isHost) : SNSessionFactory() {
        _isHost = isHost;
    }
    
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {
        if(_isHost) {
            return std::make_unique<SampleNetSession>(std::move(socket));
        } else {
            return std::make_unique<SampleNetClientSession>(std::move(socket));
        }
    }

private:
    bool _isHost;

};


#endif /* TestNetSession_h */
