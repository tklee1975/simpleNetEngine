//
//  BinSerializer.h
//  CoreLib
//
//  Created by kenlee on 31/3/2021.
//
// Reference:
//      https://github.com/SimpleTalkCpp/libsita/blob/master/src/core/src/sita_core/base/BinSerializer.h
#ifndef _BIN_SERIALIZER
#define _BIN_SERIALIZER

#include "CoreLib.h"        // ken: Q: is it good?


namespace simpleNet {
    class SNBinSerializer : public NonCopyable {
    public:
        SNBinSerializer(SNVector<u8> &buffer) : _buffer(&buffer){}   //Vector<u8>& buf) : _buf(&buf) {} why &buf ?
        
        void io(i8& value)     { _ioFixed(value); }
        void io(i16& value)    { _ioFixed(value); }
        void io(i32& value)    { _ioFixed(value); }
        void io(i64& value)    { _ioFixed(value); }
        
        void io(u8 & value)     { _ioFixed(value); }
        void io(u16 & value)    { _ioFixed(value); }
        void io(u32 & value)    { _ioFixed(value); }
        void io(u64 & value)    { _ioFixed(value); }

        
        void ioRaw(u8* data, size_t dataSize) {
                auto* src = _reserveBuffer(dataSize);
                std::copy(data, data+dataSize, src);
            }

        
        // this is for testing
        void writeInt(const int &value);
        
        void dumpBuffer(size_t size, char style='x');   // style='x' for HEX, 'd' for 'decimal'
    protected:
        SNVector<u8> * _buffer;
        
    private:
        template<class T> void _ioFixed(T& value);
        u8* _reserveBuffer(size_t n);
    };



    // Increase the buffer, and return the head of the just-reserved buffer
  

    // Implementation
    
    template<class T>
    void SNBinSerializer::_ioFixed(T& value)
    {
        auto *p = _reserveBuffer(sizeof(value));
        
        T *typePtr = reinterpret_cast<T *>(p);
        
        *typePtr = value;
    }
}
#endif
