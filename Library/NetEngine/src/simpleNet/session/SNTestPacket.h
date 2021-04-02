//
//  SNTestPacket.hpp
//  net_engine_test
//
//  Created by kenlee on 2/4/2021.
//

#ifndef SNTestPacket_hpp
#define SNTestPacket_hpp

#include "../component/SNPacket.h"
#include <simpleNet/CoreLib.h>
namespace simpleNet {

class SNTestPacket {
public:
    u32 cmd;
    i32 startIndex = 0;
    i32 size = 0;
    
    SNTestPacket(){}
    SNTestPacket(i32 _start, i32 _size);
    
    void fromBuffer(const SNVector<u8>& buf);
    void toBuffer(SNVector<u8>& buf);
    std::string toString();
private:
    SNVector<u16> _data;
};

}

#endif /* SNTestPacket_hpp */
