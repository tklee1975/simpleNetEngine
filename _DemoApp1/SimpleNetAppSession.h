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
    std::shared_ptr<SimpleNetApp> app;
    bool isHost;
    
    SimpleHostSession(SNSocket &&);
    ~SimpleHostSession();
    
    virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    
    void extractCommands(
                std::vector<u8> &buf, std::vector<SNString> &commands);
    
private:
    std::vector<char> _remainCommandBuf;    // ken: store the incomplete command
    std::vector<SNString> _cmdList;
};


class SimpleSessionFactory : public SNSessionFactory {
public:
    SimpleSessionFactory(std::shared_ptr<SimpleNetApp> app, bool isHost) : SNSessionFactory() {
        _isHost = isHost;
        _app = app;
    }
    
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {        
        auto ptr = std::make_unique<SimpleHostSession>(std::move(socket));
        ptr->app = _app;
        ptr->isHost = _isHost;
        return ptr;
    }
   
private:
    bool _isHost;
    std::shared_ptr<SimpleNetApp> _app;

};

#endif /* SimpleNetAppSession_h */
