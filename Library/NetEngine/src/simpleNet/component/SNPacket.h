//
//  SNPacket.h
//  SimpleNet
//
//  Created by kenlee on 2/4/2021.
//

#ifndef SNPacket_h
#define SNPacket_h

#include <simpleNet/CoreLib.h>
namespace simpleNet {

class SNPacketHeader {
public:
    using Len = u16;        // Length of the main packet (not include the header)
    using Cmd = u32;        // Command of the packet
                            // ken: todo add version

    Len len = 0;
    Cmd cmd = 0;

    template<class SE>      // ken: Serializer or deserializer 
    void io(SE& se) {
        se.io(len);
        se.io(cmd);
    }
    int getDataLength() {
        return sizeof(len) + sizeof(cmd);
    }
    std::string toString();
};

class SNPacket {
public:
   
    void writeBuffer(const SNVector<u8>& buf);
    void readBuffer(SNVector<u8>& buf);
};

}
#endif /* SNPacket_h */
