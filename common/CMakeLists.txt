project(Common)

set(EIGEN_BUILD_DOC OFF CACHE INTERNAL "")
set(EIGEN_BUILD_TESTING OFF CACHE INTERNAL "")

add_subdirectory("thirdparty/eigen")

set(BINARY_VERSION common)

add_library(${BINARY_VERSION} STATIC
    "string/stringutil.cpp"
    "filesystem/file.cpp"
    "filesystem/filesystem.cpp"
    "interface.cpp"
    "appframework/system.cpp"
    "appframework/application.cpp"
    "appframework/appframework.cpp"
)

target_link_libraries(${BINARY_VERSION} PUBLIC eigen)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)