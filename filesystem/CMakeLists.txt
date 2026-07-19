project(FileSystem)
set(BINARY_VERSION filesystem)

add_library(${BINARY_VERSION} SHARED
    "private/cfilesystem.cpp"
    private/cfile.cpp
)

target_link_libraries(${BINARY_VERSION} PRIVATE winmm User32 Gdi32 Shell32 common)

target_include_directories(${BINARY_VERSION}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private
        ../common
)

# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     thirdparty/glad/include
#     ../common
# )