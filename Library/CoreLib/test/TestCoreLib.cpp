//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <simpleNet/CoreLib.h>
#include <simpleNet/BinSerializer.h>
#include <simpleNet/BinDeserializer.h>


using namespace simpleNet;
using namespace std;

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
    se.dumpBuffer(10);
    
    //
    u8 result[10];
    SNBinDeserializer de(buffer);
    
    de.ioRaw(result, 10);
    for(u8 byte : result) { printf("%02x ", byte); }
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
    
    testRaw();
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
    if(strcasecmp(argv[1], "all") == 0) {
        runAllTest();
    } else {
        runSingleTest();
    }

    return 0;
} 
