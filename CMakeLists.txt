cmake_minimum_required(VERSION 3.10.0)
project(wlang VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# add_subdirectory(ext/wabt)
add_subdirectory(ext/binaryen)

add_subdirectory(tests)

add_library(wlang
    header.hpp
    codegen.hpp codegen.cpp
    langsyntax.hpp langsyntax.cpp
    token.hpp token.cpp
    stmt.hpp stmt.cpp
    expr.hpp expr.cpp
    const.hpp const.cpp
    wlang.cpp)

target_include_directories(wlang PUBLIC ext/binaryen/src)

# target_link_libraries(wlang wabt)
target_link_libraries(wlang binaryen)