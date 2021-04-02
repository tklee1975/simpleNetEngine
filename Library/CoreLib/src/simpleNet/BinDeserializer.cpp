//
//  BinDeserializer.cpp
//  CoreLib
//
//  Created by kenlee on 2/4/2021.
//

#include "BinDeserializer.h"

namespace simpleNet {
void SNBinDeserializer::readInt(int &value) {        // this is for study the logic
    auto* p = _moveCursor(sizeof(value));
    const int *intPtr = reinterpret_cast<const int *>(p);
    
    value = *intPtr; 
}
// Increase the buffer, and return the head of the just-reserved buffer
const u8* SNBinDeserializer::_moveCursor(size_t n)
{
    // ken: TODO
//    if (remain() < n) {
//        throw std::exception("BinDeserializer out of range");
//    }
    
    const u8* old = _cur;
    _cur += n;
    return old;
}
}

