//
//  SNPacket.cpp
//  net_engine_test
//
//  Created by kenlee on 2/4/2021.
//

#include "SNPacket.h"

namespace simpleNet {


std::string SNPacketHeader::toString()
{
    char str[100];
    sprintf(str, "len=%d cmd=%d", len, cmd);
    
    return std::string(str);
}

}
