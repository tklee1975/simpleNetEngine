//
//  SNTestPacket.cpp
//  net_engine_test
//
//  Created by kenlee on 2/4/2021.
//

#include "SNTestPacket.h"
#include <fmt/core.h>

//class SNTestPacket {
//public:
//
//    void writeBuffer(const SNVector<u8>& buf);
//    void readBuffer(SNVector<u8>& buf);
namespace simpleNet {

const u32 kCmdID = 100;

SNTestPacket::SNTestPacket(i32 _start, i32 _size)
    : startIndex(_start)
    , size(_size)
    , cmd(kCmdID)    
{
    _data.resize(_size);
    _data.clear();
    i32 value = startIndex;
    for(int i=0; i<size; i++) {
        _data.push_back(value);
        value++;
    }
}

void SNTestPacket::fromBuffer(const SNVector<u8>& buf)
{
    //data.resize
    int dataLen = buf.size();
    int dataArraySize = dataLen / sizeof(u16);
    
    _data.resize(dataArraySize);
    SNBinDeserializer de(buf);
    for(int i=0; i<dataArraySize; i++) {
        de.io(_data[i]);
    }

}

void SNTestPacket::toBuffer(SNVector<u8>& buf)
{
    SNBinSerializer se(buf);
    for(int i=0; i<_data.size(); i++) {
        se.io(_data[i]);
    }

}

std::string SNTestPacket::toString(){
    //fm
    //return "";
    //fmt::sprint
    std::string result;
    char temp[20];
    
    for(int i=0; i<_data.size(); i++) {
        sprintf(temp, "%03d ", _data[i]);
        result += temp;
    }
    
    return result;
}

}
