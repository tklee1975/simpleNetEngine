//
//  Platform.h
//  SimpleNet
//
//  Created by kenlee on 4/4/2021.
//

#pragma once

// Detection for Objective C
#ifdef __OBJC__
    #define SN_OBJC        1
#else
    #define SN_OBJC        0
#endif

//

// Detect Compiler and Define value
#if defined(__clang__)
    #define  SN_COMPILER_CLANG    1
    #include "DetectCompilerGcc.h"

#elif defined(__GNUC__)
    #define SN_COMPILER_GCC        1
    #include "DetectCompilerGcc.h"

#elif defined(_MSC_VER)
    #define SN_COMPILER_VC        1
    #include "DetectCompilerVc.h"

#endif


