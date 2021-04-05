//
//  DetectCompilerGcc.h
//  SimpleNet
//
//  Created by kenlee on 4/4/2021.
//

#pragma once

#if ! (SN_COMPILER_CLANG | SN_COMPILER_GCC)
    #error
#endif

// Checking the cpp version
#if __cplusplus >= 199711L
    #define SN_CPLUSPLUS_03    1
#endif

#if __cplusplus >= 201103L
    #define SN_CPLUSPLUS_11    1
#endif

#if __cplusplus >= 201402L
    #define SN_CPLUSPLUS_14    1
#endif

#if __cplusplus >= 201703L
    #define SN_CPLUSPLUS_17    1
#endif

#if __cplusplus >= 202002L
    #define SN_CPLUSPLUS_20    1
#endif




#if SN_COMPILER_CLANG
    #define SN_TYPE_HAS_SIZE_T        0  //linux
    #define SN_TYPE_HAS_SSIZE_T        0  //linux

    #define SN_OPTIMIZE_OFF            _Pragma("clang optimize off")
#else
    #define SN_TYPE_HAS_SIZE_T        0  //linux
    #define SN_TYPE_HAS_SSIZE_T        0  //linux

    #define SN_OPTIMIZE_OFF            _Pragma("GCC optimize(\"O0\")")
#endif

// ken: ???
// ken: DLL Import/Export  ???
#if __GNUC__ >= 4
    #define SN_DLL_EXPORT            __attribute__ ((visibility ("default")))
    #define SN_DLL_IMPORT            // __attribute__ ((visibility ("hidden")))
#else
    #define SN_DLL_EXPORT
    #define SN_DLL_IMPORT
#endif


// Ken: ??
#if SN_GEN_CONFIG_Debug
    #define    SN_INLINE         inline
#else
    #define    SN_INLINE        inline //__attribute__( (always_inline) )
#endif

// CPU

#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64) || defined(__amd64__)
    #define SN_CPU_X86_64      1
    #define SN_CPU_ENDIAN_LITTLE        1

#elif defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
    #define SN_CPU_X86         1
    #define SN_CPU_ENDIAN_LITTLE        1

#elif defined(__POWERPC__)
    #define SN_CPU_POWERPC     1
    #define SN_CPU_ENDIAN_BIG        1

#elif defined(__aarch64__)
    #define SN_CPU_ARM64 1

    #if defined(__ARMEL__) || defined(__AARCH64EL__)
        #define SN_CPU_ENDIAN_LITTLE    1
    #elif defined(__ARMEB__) || defined(__AARCH64EB__)
        #define SN_CPU_ENDIAN_BIG        1
    #else
        #error unknown ARM CPU endian
    #endif

#elif defined(__arm__)
    #define SN_CPU_ARM 1

    #if defined(__ARMEL__) || defined(__AARCH64EL__)
        #define SN_CPU_ENDIAN_LITTLE    1
    #elif defined(__ARMEB__) || defined(__AARCH64EB__)
        #define SN_CPU_ENDIAN_BIG        1
    #else
        #error unknown ARM CPU endian
    #endif
#endif

#if    defined(__ARM_NEON__) || defined(__ARM_NEON)
    #define SN_CPU_FEATURE_ARM_NEON
#endif

