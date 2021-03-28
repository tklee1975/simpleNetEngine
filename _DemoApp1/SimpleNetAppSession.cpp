//
//  SimpleNetAppSession.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "SimpleNetAppSession.h"
#include "SimpleNetApp.h"


SimpleHostSession::SimpleHostSession(SNSocket && _sock, SimpleNetApp &_app, bool _isHost)
    : SNSession(std::move(_sock))
    , mainApp(_app)
    , isHost(_isHost)
{
    
}

SimpleHostSession::~SimpleHostSession()
{
}


void SimpleHostSession::onConnect()
{
    std::cout << "Connected to client\n";
    
    mainApp.onConnected();
}

void SimpleHostSession::onDisconnect()
{
    std::cout << "Client disconnected\n";
}

void SimpleHostSession::onRecvData(std::vector<u8> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    
    buf[nRead] = '\0';
    
    std::vector<u8> cleanBuffer = std::vector<u8>(buf.begin(), buf.begin()+nRead);  // ken: HACK: how to make it better, no need the copy action
    
    _cmdList.clear();
    extractCommands(cleanBuffer, _cmdList);
    
    for(int i=0; i<_cmdList.size(); i++) {
        mainApp.onReceiveCommand(_cmdList[i]);
    }
}


void SimpleHostSession::extractCommands(
        std::vector<u8> &buf, std::vector<SNString> &_outCmds)
{
    std::string debugStr;
    std::vector<SNString> result;
    
    //result.push_back(SNString("testing"));
    
    std::vector<u8>::iterator it;
    std::vector<u8>::iterator start;

    char sep = '\n';
    
    start = buf.begin();
    for(;;) {
        it = std::find(start, buf.end(), sep);
        if(it == buf.end()) {   // Nothing find
            
            //std::vector<char> part = std::vector<char>(start, it);
            //debugStr = std::string(part.begin(), part.end());
            // std::cout << "debugStr: [" << debugStr << "]\n";
            
            _remainCommandBuf.clear();
            _remainCommandBuf.insert(_remainCommandBuf.end(), start, buf.end());
            _remainCommandBuf.push_back('\0'); // ken: prevent adding unknow characters
            //_remainCommandBuf.
            
            break;
        }
        
        // Construct the command
        std::string newPart(start, it);
        
        
        if(_remainCommandBuf.size() > 0) {
            newPart.append(_remainCommandBuf.begin(), _remainCommandBuf.end());
           _remainCommandBuf.clear();
        }
        
        SNString command;
        command.append(newPart);
        _outCmds.emplace_back(command);

        start = it+1;
        
        if(start == buf.end()) {
            break;
        }
    }
}
