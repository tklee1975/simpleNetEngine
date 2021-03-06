#include <stdio.h>
#include <cmath>
#include <iostream>
//#include <fmt/core.h>
#include "pch.h"

#include <NetEngine.h>
#include <CoreLib.h>



int main() {
    //fmt::print("Corelib Version: {}.\n", KC_CORE_LIB_VERSION);
    printf("Corelib Version: %s\n", KC_CORE_LIB_VERSION);
    printf("NetEngine Version: %s\n", KC_NET_ENGINE_VERSION);
    
    return 0;
}