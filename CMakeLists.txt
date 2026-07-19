cmake_minimum_required(VERSION 2.6...3.22 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    # add_compile_options(/MP) # parallel build (use all cores, or as many as configured in VS)
    # add_compile_options(/W3) # TODO: was /W4, caused trouble with VS2019 (and/or its integrated CMake? or only HarrieVG's setup?)
    # add_compile_options(/we4840) # treat as error when passing a class to a vararg-function (probably printf-like)
    # # treat several kinds of truncating int<->pointer conversions as errors (for more 64bit-safety)
    # add_compile_options(/we4306 /we4311 /we4312 /we4302)
    # # ignore the following warnings:
    # add_compile_options(/wd4100) # unreferenced formal parameter
    # add_compile_options(/wd4127) # conditional expression is constant
    # add_compile_options(/wd4244) # possible loss of data
    # add_compile_options(/wd4245) # signed/unsigned mismatch
    # add_compile_options(/wd4267) # possible loss of data
    # add_compile_options(/wd4714) # 'function' marked as __forceinline not inlined
    # add_compile_options(/wd4996) # 'function': was declared deprecated
    # add_compile_options(/wd4068) # unknown pragma
    # add_compile_options(/wd4458) # declaration of 'variable' hides class member
    set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG /Od /Zi /MDd")
    set(CMAKE_C_FLAGS_RELEASE "/Ox /Oy /MD")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ox /Oy /Zi /MD")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Ox /Oy /Os /MD")
    # use 8MB stack instead of 1MB, so big models don't overflow it with _alloca()
    set(ldflags "${ldflags} /STACK:8388608")
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()

set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO})
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG ${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-DNDEBUG ${CMAKE_C_FLAGS_MINSIZEREL}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")

add_subdirectory(common)
add_subdirectory(filesystem)
add_subdirectory(media)
add_subdirectory(rendersystemgl)
add_subdirectory(basicapp)
# add_subdirectory(ganderED)
# add_subdirectory(engine)
# add_subdirectory(seabed)
# add_subdirectory(worldcraft)