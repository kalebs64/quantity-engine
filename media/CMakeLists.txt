project(Media)

set(BINARY_VERSION media)

add_subdirectory("thirdparty/SDL")
add_library(${BINARY_VERSION} SHARED
    "private/cwindow.cpp"
    "private/cmedia.cpp"
)

target_link_libraries(${BINARY_VERSION} PRIVATE winmm User32 Gdi32 Shell32 SDL3::SDL3 filesystem common)

target_include_directories(${BINARY_VERSION}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private
        ../common
)