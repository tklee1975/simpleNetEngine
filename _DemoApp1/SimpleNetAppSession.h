//
//  SimpleNetAppSession.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SimpleNetAppSession_h
#define SimpleNetAppSession_h

#include <stdio.h>

#include <stdio.h>
#include <simpleNet/NetEngine.h>

using namespace simpleNet;

class SimpleNetApp;

class SimpleHostSession : public SNSession {
public:
    SimpleNetApp *app;
    bool isHost;
    
    SimpleHostSession(SNSocket *);
    virtual void onRecvData(std::vector<char> &buf, size_t &nRead);
    virtual void onConnect();
    virtual void onDisconnect();
    
    std::vector<SNString> extractCommands(std::vector<char> &buf);
    //std::vector<SNString> extractCommands(std::vector<char> &buf);
private:
    std::vector<char> _remainCommandBuf;    // ken: store the incomplete command 
};


class SimpleSessionFactory : public SNSessionFactory {
public:
    SimpleSessionFactory(SimpleNetApp *app, bool isHost) : SNSessionFactory() {
        _isHost = isHost;
        _app = app;
    }
    
    virtual SNSession *create(SNSocket *socket) {
        SimpleHostSession *session = new SimpleHostSession(socket);
        
        //session->isHost = _isHost;
        session->app = _app;
        session->isHost = _isHost;
        
        return session;
//        if(_isHost) {
//            return new SampleNetSession(socket);
//        } else {
//            return new SampleNetClientSession(socket);
//        }
    }
private:
    bool _isHost;
    SimpleNetApp *_app;

};

#endif /* SimpleNetAppSession_h */
