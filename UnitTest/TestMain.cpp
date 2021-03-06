//#define DOCTEST_CONFIG_IMPLEMENT
//#include "doctest.h"
#include <stdio.h>
#include <iostream>
#include <CoreLib.h>

void testLog() {
    simpleNet::log("testing: %d %d", 123, 2312);
}

void test1() {
    std::cout << "Test1\n";
}

void runSingleTest() {
    std::cout << "Run Single Test\n";
    testLog();
    // test1();
}

void runAllTest() {
    std::cout << "Run All Test\n";
    testLog();
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
