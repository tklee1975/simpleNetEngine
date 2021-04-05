#include <stdio.h>
#include <cmath>
#include <iostream>
#include <fmt/core.h>
#include "pch.h"


#include <simpleNet/NetEngine.h>
#include <simpleNet/CoreLib.h>

#include "DemoApp2.h"

int main() {
    fmt::print("Demp Net App2\n");
    fmt::print("Corelib Version: {}.\n", KC_CORE_LIB_VERSION);
    fmt::print("NetEngine Version: {}.\n", KC_NET_ENGINE_VERSION);
    
    auto app = DemoApp2();
    if(app.init() == false) {
        std::cout << "Fail to init\n";
        return 0;
    }
    
    app.run();
    
    return 0;
}


