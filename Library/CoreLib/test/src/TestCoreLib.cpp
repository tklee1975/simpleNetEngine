//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <simpleNet/CoreLib.h>
#include <simpleNet/BinSerializer.h>
#include <simpleNet/BinDeserializer.h>


using namespace simpleNet;
using namespace std;

enum class TestType {
    Type1 = 1,
    Type2 = 2,
};

// enumInt
void testEnumInt() {
    TestType t1 = TestType::Type1;
    TestType t2 = TestType::Type2;
    
    std::cout << " type=" << enumInt(t1) << "\n";
    std::cout << " type=" << enumInt(t2) << "\n";
}

void testEndian()
{

#if SN_CPU_ENDIAN_LITTLE
    fmt::print("Using Little Endian now\n");
#elif SN_CPU_ENDIAN_BIG
    fmt::print("Using Big Endian now\n");
#endif
    i16 v16 = 0x1234;
    
    fmt::print("Testing Big Endian\n");

    
    i16 toHost = BigEndian::ToHost::get(v16);
    i16 fromHost = BigEndian::FromHost::get(toHost);


    fmt::print("Normal    : {:x}\n", v16);
    fmt::print("toHost    : {:x}\n", toHost);
    fmt::print("fromHost  : {:x}\n", fromHost);


    fmt::print("Testing Little Endian\n");
    toHost = LittleEndian::ToHost::get(v16);
    fromHost = LittleEndian::FromHost::get(toHost);

    
    fmt::print("Normal    : {:x}\n", v16);
    fmt::print("toHost    : {:x}\n", toHost);
    fmt::print("fromHost  : {:x}\n", fromHost);

}



void testPlatformVersion()
{
    fmt::print("_CPLUSPLUS_11: {}\n", SN_CPLUSPLUS_11);
    fmt::print("_CPLUSPLUS_14: {}\n", SN_CPLUSPLUS_14);
    fmt::print("_CPLUSPLUS_17: {}\n", SN_CPLUSPLUS_17);
    //fmt::print("_CPLUSPLUS_20: {}", SN_CPLUSPLUS_20);
#ifdef SN_CPU_X86
    fmt::print("X86\n");
#elif SN_CPU_X86_64
    fmt::print("X86 64\n");
#elif SN_CPU_POWERPC
    fmt::print("POWERPC\n");
#elif SN_CPU_ARM64
    fmt::print("ARM64\n");
#else
    fmt::print("Unknown CPU\n");
#endif
//
//#define SN_CPU_X86         1
//
//#elif defined(__POWERPC__)
//#define SN_CPU_POWERPC     1
//
//#elif defined(__aarch64__)
//#define SN_CPU_ARM64 1
//
//#if defined(__ARMEL__) || defined(__AARCH64EL__)
//    #define SN_CPU_ENDIAN_LITTLE    1
//#elif defined(__ARMEB__) || defined(__AARCH64EB__)
//    #define SN_CPU_ENDIAN_BIG        1
//#else
//    #error unknown ARM CPU endian
//#endif
//
//#elif defined(__arm__)
//#define SN_CPU_ARM 1
//
//#if defined(__ARMEL__) || defined(__AARCH64EL__)
//    #define SN_CPU_ENDIAN_LITTLE    1
//#elif defined(__ARMEB__) || defined(__AARCH64EB__)
//    #define SN_CPU_ENDIAN_BIG        1
//#else
//    #error unknown ARM CPU endian
//#endif
//#endif
//
//#if    defined(__ARM_NEON__) || defined(__ARM_NEON)
//#define SN_CPU_FEATURE_ARM_NEON
//#endif

}

void testByteWrap()
{
    i16 value = 0x1234;
    i16 swapValue = ByteOrder::ByteSwap::get(value);
    
    printf("Normal: [%04x]\n", value);
    printf("Swap  : [%04x]\n", swapValue);
    
    i32 v32 = 0x12345678;
    i32 swap32 = ByteOrder::ByteSwap::get(v32);
    
    printf("Normal: [%08x]\n", v32);
    printf("Swap  : [%08x]\n", swap32);
    
            //0xFF00FF00FF00FF00ULL
    i64 v64 = 0x1234567890ABCDEFuLL;
    i64 swap64 = ByteOrder::ByteSwap::get(v64);
    
    fmt::print("Normal: [{:x}]\n", v64);
    fmt::print("Swap  : [{:x}]\n", swap64);
    //printf("Normal: [%016x]\n", (long long) v64);
    //printf("Swap  : [%016x]\n", swap64);
}

void testDumpHex() {
    std::cout << "Dump Hex\n";
    
    
    SNVector<u8> data;
    data.resize(10);
    for(int i=0; i<10; i++) {
        data[i] = 50 + i;
    }
    
    SNString result;
    SNStringUtil::binToHex(result, data);
    std::cout << "RESULT: " << result.str() << "\n";
    
    SN_DUMP_HEX(data);
    //std::string str(data.begin(), data.end());
    //cout << "STR: [" << str << "]\n";
}

//io_raw
void testRaw()
{
    SNVector<u8> buffer;
    
    SNBinSerializer se(buffer);

    u8 data[10];
    for(int i=0; i<10; i++) {
        data[i] = 100 + i;
    }
    
    se.ioRaw(data, 10);
    se.ioRaw(data, 10);
    se.dumpBuffer(10);
    
    cout << "BufferSize: " << buffer.size() << "\n";
    //
    u8 result[10];
    SNBinDeserializer de(buffer);
    
    de.ioRaw(result, 10);
    //for(u8 byte : result) { printf("%02x ", byte); }
    printf("\n");
}

void testFixed()
{
    SNVector<u8> buffer;
    
    SNBinSerializer se(buffer);
    i8  a = 100;
    i16 b = 255;
    
    
    se.io(a);
    se.io(b);
    //
    
    se.dumpBuffer(10, 'd');
    
    SNBinDeserializer de(buffer);
    i8 result8;
    i16 result16;
    
    de.io(result8);
    de.io(result16);

    //cout << result8 << " " << result16 << "\n";
    printf("%x ", result8);
    
//    SNBinDeserializer de(buffer);
//    int result;
//    de.readInt(result);
//    cout << "Result: " << result << "\n";
//    
//    de.readInt(result);
//    cout << "Result: " << result << "\n";
}



void testSerializeWriteInt() {
    SNVector<u8> buffer;
    
    SNBinSerializer se(buffer);
    
    int data = 128;
    se.writeInt(data); //
    
    data = 100;
    se.writeInt(data); //
    //
    
    se.dumpBuffer(10, 'd');
    
    SNBinDeserializer de(buffer);
    int result;
    de.readInt(result);
    cout << "Result: " << result << "\n";
    
    de.readInt(result);
    cout << "Result: " << result << "\n";
}



void test1() {
    std::cout << "Test1\n";
}

// For Single and Temp testing
void runSingleTest() {
    std::cout << "Run Single Test\n";
    
    // testEnumInt();
    testEndian();
    // testPlatformVersion();
    // testByteWrap();
    // testDumpHex();
    // testRaw();
    // testFixed();
    // testSerializeWriteInt();
    // test1();
    
    std::cout << "End of Single Test\n";
}

void runAllTest() {
    std::cout << "Run All Test\n";
    
    test1();
}

int main(int argc, char** argv) {
    printf("Running UnitTest: %d\n", argc);

    if(argc <= 1) {
        runSingleTest();
        return 0;
    }
    // std::cout << "Input: " <<  argv[1] << "\n";
    if(my_strcasecmp(argv[1], "all") == 0) {
        runAllTest();
    } else {
        runSingleTest();
    }

    return 0;
} 
