//
//  Log.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef Log_hpp
#define Log_hpp

#include <stdio.h>

#define MAX_LOG_LENGTH 2048

namespace simpleNet {
    void log(const char * format, ...);
}


#endif /* Log_hpp */
