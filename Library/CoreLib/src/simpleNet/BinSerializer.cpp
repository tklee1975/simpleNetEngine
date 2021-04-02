//
//  BinSerializer.c
//  CoreLib
//
//  Created by kenlee on 31/3/2021.
//

#include "BinSerializer.h"

namespace simpleNet {
u8* SNBinSerializer::_reserveBuffer(size_t n)
{
    size_t oldSize = _buffer->size();
    // LOG("oldSize=%d", oldSize);
    _buffer->resize(oldSize + n);
    return _buffer->data() + oldSize;
}

void SNBinSerializer::writeInt(const int &value) {        // this is for study the logic
    auto *p = _reserveBuffer(sizeof(value));
    
    int *intPtr = reinterpret_cast<int *>(p);
    
    *intPtr = value;
}

void SNBinSerializer::dumpBuffer(size_t size, char style)   
{
    if(size >= _buffer->size()) {
        size = _buffer->size();
    }
    
    auto buf = *_buffer;
    for(int i=0; i<size; i++) {
        if(style == 'x') {
            printf("%02x ", buf[i]);           // ken: todo: change to fmt::print
        } else {
            printf("%03d ", buf[i]);           // ken: todo: change to fmt::print
        }
    }
    std::cout << "\n";           // ken: todo: change to fmt::print
}



}
