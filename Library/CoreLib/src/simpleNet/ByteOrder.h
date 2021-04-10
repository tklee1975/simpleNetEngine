//
//  ByteOrder.hpp
//  SimpleNet
//
//  Created by kenlee on 4/4/2021.
//

#pragma once

#include "Common.h"
#include "Type.h"
#include "platform/Platform.h"

namespace simpleNet {

/**
 * Ken: Note:
 * For representing 0x12345678 value
 * BigEndian ByteOrder      is Left to Right: result: 0x12345678
 * Little Endian ByteOrder  is Right to Left: result: 0x78563412
 */
class ByteOrder {
public:
    class Straight {
    public:
        constexpr static u8  get(u8  v) { return v; }   // ken: constexpr calculate the value in compile time
        constexpr static u16 get(u16 v) { return v; }
        constexpr static u32 get(u32 v) { return v; }
        constexpr static u64 get(u64 v) { return v; }

        constexpr static i8  get(i8  v) { return v; }
        constexpr static i16 get(i16 v) { return v; }
        constexpr static i32 get(i32 v) { return v; }
        constexpr static i64 get(i64 v) { return v; }

        constexpr static f32 get(f32 v) { return v; }
        constexpr static f64 get(f64 v) { return v; }
    };

    //https://blog.gtwang.org/programming/difference-between-big-endian-and-little-endian-implementation-in-c/
    class ByteSwap {
    public:
        constexpr static u8  get(u8  v) {
            return v;
        }
        
        constexpr static u16 get(u16 v) {
            return (u16)(v >> 8) | (v << 8);
        }
        
        // AA BB CC DD
        //
        // DD CC BB AA
        constexpr static u32 get(u32 v) {
            v =   ((v << 8) & 0xFF00FF00UL)     // BB 00 DD 00
                | ((v >> 8) & 0x00FF00FFUL);    // 00 AA 00 CC
            return (v>>16) | (v<<16);           // DD 00 BB 00 | 00 CC 00 AA
        }
        
        // 77 88 99 AA BB CC DD EE FF
        //
        constexpr static u64 get(u64 v) {
            v =   ((v<< 8) & 0xFF00FF00FF00FF00ULL)
                | ((v>> 8) & 0x00FF00FF00FF00FFULL);
            
            v =  ((v<<16) & 0xFFFF0000FFFF0000ULL)
               | ((v>>16) & 0x0000FFFF0000FFFFULL);
            
            return (v>>32) | (v<<32);
        }

        constexpr static i8  get(i8  v) { return static_cast<i8 >(get(static_cast<u8 >(v))); }
        constexpr static i16 get(i16 v) { return static_cast<i16>(get(static_cast<u16>(v))); }
        constexpr static i32 get(i32 v) { return static_cast<i32>(get(static_cast<u32>(v))); }
        constexpr static i64 get(i64 v) { return static_cast<i64>(get(static_cast<u64>(v))); }

        static f32 get(f32 v) {
            u32 tmp = get(*reinterpret_cast<const u32*>(&v));
            return *reinterpret_cast<const f32*>(&tmp);
        }
        static f64 get(f64 v) {
            u64 tmp = get(*reinterpret_cast<const u64*>(&v));
            return *reinterpret_cast<const f64*>(&tmp);
        }
    };
};


// send to/from host using LittleEndian
class LittleEndian {
public:
    
#if SN_CPU_ENDIAN_LITTLE
    using ToHost   = ByteOrder::Straight;       // No need Swap
    using FromHost = ByteOrder::Straight;
#elif SN_CPU_ENDIAN_BIG                       // Need Swap
    using ToHost   = ByteOrder::ByteSwap;
    using FromHost = ByteOrder::ByteSwap;
#endif
};

// send to/from host using BigEndian
class BigEndian {
public:
#if SN_CPU_ENDIAN_LITTLE
    using ToHost   = ByteOrder::ByteSwap;       // Need Swap
    using FromHost = ByteOrder::ByteSwap;
#elif SN_CPU_ENDIAN_BIG
    using ToHost   = ByteOrder::Straight;        // No need Swap
    using FromHost = ByteOrder::Straight;
#endif
};



// --- Namespace 
}
