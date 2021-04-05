//
//  SimpleNetAppSession.h
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#ifndef SimpleNetAppSession_h
#define SimpleNetAppSession_h

#include <simpleNet/NetEngine.h>

using namespace simpleNet;

class DemoApp2;

class DemoApp2Session : public SNNetSession
{
public:
    DemoApp2 &mainApp;
    bool isHost;
    
    DemoApp2Session(SNSocket && sock, DemoApp2 &_app, bool isHost);
    ~DemoApp2Session();
    
    virtual void onRecvPacketBuffer(const SNPacketHeader::Cmd &cmd,
                                    const SNVector<u8> &packetBuffer) override;
    //virtual void onRecvData(std::vector<u8> &buf, size_t &nRead) override;
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    
};


class DemoApp2SessionFactory : public SNSessionFactory {
public:
    
    DemoApp2SessionFactory(DemoApp2& appRef, bool isHost)
        : SNSessionFactory()
        , _appRef(appRef)
        , _isHost(isHost)
    {
    }
    
    virtual std::unique_ptr<SNSession> newSession(SNSocket &&socket) override {        
        auto ptr = std::make_unique<DemoApp2Session>(
                            std::move(socket), _appRef, _isHost);
        return ptr;
    }
   
private:
    bool _isHost;
    DemoApp2& _appRef;
};

#endif /* SimpleNetAppSession_h */
