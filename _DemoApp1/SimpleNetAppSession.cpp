//
//  SimpleNetAppSession.c
//  test_gui
//
//  Created by kenlee on 14/3/2021.
//

#include "SimpleNetAppSession.h"
#include "SimpleNetApp.h"

SimpleHostSession::SimpleHostSession(SNSocket *sock) : SNSession(sock)
{
    
}

void SimpleHostSession::onConnect()
{
    std::cout << "Connected to client\n";
    if(app != nullptr) {
        app->onConnected();
    }
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
    
    if(app == nullptr) {
        return;
    }
    
    buf[nRead] = '\0';
    
    std::vector<u8> cleanBuffer = std::vector<u8>(buf.begin(), buf.begin()+nRead);  // ken: HACK: how to make it better, no need the copy action
    
    _cmdList.clear();
    extractCommands(cleanBuffer, _cmdList);
    
    for(int i=0; i<_cmdList.size(); i++) {
        app->onReceiveCommand(_cmdList[i]);
    }
    
    
//    const char *msg = (const char *) buf.data();
//    std::cout << "RECEIVE: " << msg << "\n";
//    if(strlen(msg) == 0) {
//        return;
//    }
//
//    //
//    SNString cmd;
//    if(msg[0] == 'u'){
//        cmd.set("up");
//    } else if(msg[0] == 'd') {
//        cmd.set("down");
//    } else if(msg[0] == 'l') {
//        cmd.set("left");
//    } else if(msg[0] == 'r') {
//        cmd.set("right");
//    } else {
//        cmd = SNString(msg);
//    }
//
//    if(cmd.isEmpty() == false) {
//        app->onReceiveCommand(cmd);
//    }
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
           //command.append(_remainCommandBuf.data());
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
