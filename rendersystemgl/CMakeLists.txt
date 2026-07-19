project(RenderSystemGL)

set(GLSource thirdparty/glad/src/glad.c)
set(BINARY_VERSION rendersystemgl)

add_library(${BINARY_VERSION} SHARED
    ${GLSource}
    "private/cshadersystem.cpp"
    "private/crenderworld.cpp"
    "private/crendersystem.cpp"
)

target_link_libraries(${BINARY_VERSION} PRIVATE winmm User32 Gdi32 Shell32 opengl32 media filesystem common)

target_include_directories(${BINARY_VERSION}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private
        thirdparty/glad/include
        ../common
)