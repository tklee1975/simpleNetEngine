//
//  Common.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef Common_hpp
#define Common_hpp

#include <stdio.h>
#include <unistd.h> // sleep()

namespace simpleNet {
//


inline void sleep(int sec) {
#ifdef _WIN32
    Sleep(sec * 1000);
#else
    ::sleep(sec);
#endif
}

//
}

#endif /* Common_hpp */
