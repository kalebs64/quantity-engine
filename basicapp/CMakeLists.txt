project(basicapp)
set(BINARY_VERSION apptest)

add_executable(${BINARY_VERSION}
    src/main.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ../common/
)

target_link_libraries(${BINARY_VERSION} PRIVATE
    common
    filesystem
    media
    rendersystemgl
)