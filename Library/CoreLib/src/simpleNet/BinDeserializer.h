//
//  BinDeserializer.h
//  SimpleNet
//
//  Created by kenlee on 2/4/2021.
//

#ifndef BinDeserializer_h
#define BinDeserializer_h


#include "CoreLib.h"        // ken: Q: is it good?


namespace simpleNet {
    class SNBinDeserializer : public NonCopyable {
    public:
        SNBinDeserializer(const SNVector<u8> &buffer)
            : _data(buffer.data())
            , _cur(buffer.data()){}   //Vector<u8>& buf) : _buf(&buf) {} why
        
        void readInt(int &value);       // For testing
        
        void io(i8 & value)     { _ioFixed(value); }
        void io(i16 & value)    { _ioFixed(value); }
        void io(i32 & value)    { _ioFixed(value); }
        void io(i64 & value)    { _ioFixed(value); }
        
        void io(u8 & value)     { _ioFixed(value); }
        void io(u16 & value)    { _ioFixed(value); }
        void io(u32 & value)    { _ioFixed(value); }
        void io(u64 & value)    { _ioFixed(value); }
        
        void ioRaw(u8* data, size_t dataSize) {
                auto* src = _moveCursor(dataSize);
                std::copy(src, src+dataSize, data);
            }

        
    protected:
        SNVector<u8> * _buffer;
        
        const u8* _moveCursor(size_t n);
    private:
        template<class T> void _ioFixed(T& value);
        //u8* _reserveBuffer(size_t n);
  
        const u8* _data = nullptr;
        const u8* _cur  = nullptr;
        const u8* _end  = nullptr;
    };



    template<class T>
    void SNBinDeserializer::_ioFixed(T& value) {        // this is for study the logic
        auto* p = _moveCursor(sizeof(value));
        const T *dataPtr = reinterpret_cast<const T *>(p);
        
        value = LittleEndian::ToHost::get(*dataPtr);
    }

}

#endif /* BinDeserializer_h */
