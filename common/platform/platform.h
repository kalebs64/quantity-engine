#pragma once
#ifdef _MSC_VER
//prevents the compiler from generating code to initialize the vtable inside of the class' (de)constructor, thus the linker will dispose of it and save us a little memory.
#define STRIP_VTABLE __declspec(novtable)
#else
#define STRIP_VTABLE
#endif

#define stripped_vclass class STRIP_VTABLE

#ifdef _MSC_VER
#define ALIGN4      DECL_ALIGN(4)
#define ALIGN8      DECL_ALIGN(8)
#define ALIGN16     DECL_ALIGN(16)
#define ALIGN32     DECL_ALIGN(32)
#define ALIGN128    DECL_ALIGN(128)
#endif

#if defined(_WIN32)
    #define DLL_FUNC_EXPORT             extern "C" __declspec(dllexport)
    #define DLL_FUNC_IMPORT             extern "C" __declspec(dllimport)

    #define DLL_CLASS_EXPORT            __declspec(dllexport)
    #define DLL_CLASS_IMPORT            __declspec(dllimport)
#endif