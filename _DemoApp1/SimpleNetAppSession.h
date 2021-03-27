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
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    
    void extractCommands(
                std::vector<u8> &buf, std::vector<SNString> &commands);
    //std::vector<SNString> extractCommands(std::vector<char> &buf);
private:
    std::vector<char> _remainCommandBuf;    // ken: store the incomplete command
    std::vector<SNString> _cmdList;
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
