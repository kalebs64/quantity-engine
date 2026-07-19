#pragma once

typedef unsigned int            uint;
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;

typedef signed char             int8;
typedef signed short            int16;
typedef signed long             int32;
typedef signed long long        int64;

typedef float                   float32;
typedef double                  float64;

typedef uint8                   byte_t;

#ifdef _WIN64
    typedef uint64      Size_T;
    typedef int64       PtrDiff_T;
    typedef int64       IntPtr_T;
#else
    typedef uint        Size_T;
    typedef int         PtrDiff_T;
    typedef int         IntPtr_T;
#endif