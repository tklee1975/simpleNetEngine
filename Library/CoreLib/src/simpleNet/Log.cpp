//
//  Log.cpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#include "Log.h"
#include <iostream>

namespace simpleNet {
void _log(const char *format, va_list args);


void log(const char *tag, const char * format, ...)
{
    
    std::cout << tag;
    va_list args;
    
    va_start(args, format);
    //std::cout << "Log\n";
    _log(format, args);

    va_end(args);
}

void _log(const char *format, va_list args)
{
    int bufferSize = MAX_LOG_LENGTH;
    
    // Setup Buffer
    char *buf = new (std::nothrow) char[bufferSize];
    if (buf == nullptr) {
        return; // not enough memory
    }

    // ken: FIXME: Handle very long log line, change to fmt 
    int ret = vsnprintf(buf, bufferSize - 3, format, args);
    if(ret < 0) {
        printf("log too long");
        return;
    }
    // strcat(buf, "\n");
    
    //printf(format, args);
    std::cout <<  buf << "\n";
    
    delete []  buf;
}

}
