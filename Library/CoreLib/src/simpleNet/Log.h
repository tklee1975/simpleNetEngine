//
//  Log.hpp
//  SimpleNet
//
//  Created by kenlee on 6/3/2021.
//

#ifndef Log_hpp
#define Log_hpp
#pragma once

#include <stdio.h>
#include "Nocopyable.h"
#include <fmt/format.h>
#include <iostream>

#define MAX_LOG_LENGTH 2048

//#define LOG(...)       do{ simpleNet::gLog.write(\
//                                simpleNet::Log::Level::Info,\
//                                __VA_ARGS__); } while(false)

#define LOG(...)          do{ simpleNet::log("[INFO]  :", __VA_ARGS__); } while(false)
#define ERROR_LOG(...)    do{ simpleNet::log("[ERROR] :", __VA_ARGS__); } while(false)
#define DEBUG_LOG(...)    do{ simpleNet::log("[DEBUG] :", __VA_ARGS__); } while(false)

// ken: note: write a better version using fmt::fmt later
namespace simpleNet {
    void log(const char *tag, const char * format, ...);

    class Log : public NonCopyable {
        public:

        enum class Level {
            Unknown,
            Info,
            Warning,
            Error,
        };

        template<class... Args>
            void write(Level lv, const Args&... args) {
                //std::string s =
                //fmt::format(std::forward<decltype(args)>...);
                std::cout << "not yet" << "\n";
                //String s = fmt::format(SITA_FORWARD(args)...);
                //onWrite(lv, s);
            }
    };
    
    
    //extern Log gLog;
}


#endif /* Log_hpp */
