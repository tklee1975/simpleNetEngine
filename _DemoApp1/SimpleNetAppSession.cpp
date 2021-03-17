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

void SimpleHostSession::onRecvData(std::vector<char> &buf, size_t &nRead)
{
    if(nRead == 0) {
        return;
    }
    if(app == nullptr) {
        return;
    }
    
    buf[nRead] = '\0';
    
    std::vector<char> cleanBuffer = std::vector<char>(buf.begin(), buf.begin()+nRead);  // ken: HACK: how to make it better, no need the copy action
    std::vector<SNString> cmdList = extractCommands(cleanBuffer);
    
    for(int i=0; i<cmdList.size(); i++) {
        app->onReceiveCommand(cmdList[i]);
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


std::vector<SNString> SimpleHostSession::extractCommands(std::vector<char> &buf)
{
    std::string debugStr;
    std::vector<SNString> result;
    
    //result.push_back(SNString("testing"));
    
    std::vector<char>::iterator it;
    std::vector<char>::iterator start;

    char sep = '\n';
    
    start = buf.begin();
    for(;;) {
        it = std::find(start, buf.end(), sep);
        if(it == buf.end()) {   // Nothing find
            
            std::vector<char> part = std::vector<char>(start, it);
            debugStr = std::string(part.begin(), part.end());
            // std::cout << "debugStr: [" << debugStr << "]\n";
            
            _remainCommandBuf.clear();
            _remainCommandBuf.insert(_remainCommandBuf.end(), part.begin(), part.end());
            //_remainCommandBuf.
            
            break;
        }
        
        std::vector<char> part = std::vector<char>(start, it);
        //debugStr = std::string(part.begin(), part.end());
        //std::cout << "debugStr: [" << debugStr << "]\n";
        
        SNString command;

        // Append the remain buffer first
        if(_remainCommandBuf.size() > 0) {
            command.append(_remainCommandBuf.data());
            _remainCommandBuf.clear();
        }
        command.append(part.data());
        command.append("\0");
        
        
        std::cout << "command: [" << command.c_str() << "]\n";
        result.push_back(command);
        
        // Increase the iterator
        start = it+1;
        
        if(start == buf.end()) {
            break;
        }
    }
    
    return result;
}
