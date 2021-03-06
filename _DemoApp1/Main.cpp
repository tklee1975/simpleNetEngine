#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fmt/core.h>
#include "pch.h"

#include <NetEngine.h>
#include <CoreLib.h>



int main() {
    fmt::print("Simple Network Engine\n");
    fmt::print("Corelib Version: {}.\n", KC_CORE_LIB_VERSION);
    fmt::print("NetEngine Version: {}.\n", KC_NET_ENGINE_VERSION);
    
    simpleNet::log("Server is started!");
    
    
    return 0;
}
