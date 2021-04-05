//
//  DetectCompilerVc.h
//  SimpleNet
//
//  Created by kenlee on 4/4/2021.
//

#pragma once

#pragma warning(disable: 4668) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'

//
//  DetectCompilerGcc.h
//  SimpleNet
//
//  Created by kenlee on 4/4/2021.
//

#pragma once

#if ! (SN_COMPILER_VC)
    #error
#endif

// Checking the cpp version
#if _MSVC_LANG >= 199711L
    #define SN_CPLUSPLUS_03    1
#endif

#if _MSVC_LANG >= 201103L
    #define SN_CPLUSPLUS_11    1
#endif

#if _MSVC_LANG >= 201402L
    #define SN_CPLUSPLUS_14    1
#endif

#if _MSVC_LANG >= 201703L
    #define SN_CPLUSPLUS_17    1
#endif

#if _MSVC_LANG >= 202002L
    #define SN_CPLUSPLUS_20    1
#endif



#define SN_TYPE_HAS_SIZE_T        0
#define SN_TYPE_HAS_SSIZE_T       0
#define SN_TYPE_HAS_LONGLONG      0

// ken: DLL Import/Export  ???
#define SN_DLL_EXPORT            _declspec(dllexport)
#define SN_DLL_IMPORT            _declspec(dllimport)


// Ken: ??
#if 0 // SITA_GEN_CONFIG_Debug
    #define    SN_INLINE        inline
#else
    #define    SN_INLINE        __forceinline
#endif

#if _MSC_VER < 1600
    #define    nullptr    NULL
#endif


// CPU
#if _M_X64
    #define SN_CPU_X86_64              1
    #define SN_CPU_ENDIAN_LITTLE       1
    #define SN_CPU_FEATURE_SSE1        1
    #define SN_CPU_FEATURE_SSE2        1
    #define SN_CPU_FEATURE_SSE3        1

#elif _M_PPC
    #define SN_CPU_POWERPC             1
    #define SN_CPU_ENDIAN_BIG          1
#else
    #define SN_CPU_x86                 1
    #define SN_CPU_ENDIAN_LITTLE       1
#endif

#if _WIN64
    #define SN_OS_WIN64                1
    #define SN_OS_WINDOWS              1
#elif _WIN32
    #define SN_OS_WIN32                1
    #define SN_OS_WINDOWS              1
#elif _WINCE
    #define SN_OS_WinCE                1
    #define SN_OS_WINDOWS              1
#endif
