cmake_minimum_required(VERSION 3.10.0)
project(prometheus VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# add_subdirectory(ext/wabt)
add_subdirectory(ext/binaryen)

add_subdirectory(tests)

add_library(prometheus
    header.hpp
    codegen.hpp codegen.cpp
    langsyntax.hpp langsyntax.cpp
    token.hpp token.cpp
    stmt.hpp stmt.cpp
    expr.hpp expr.cpp
    const.hpp const.cpp
    type.hpp type.cpp
    prometheus prometheus.cpp)

target_include_directories(prometheus PUBLIC ext/binaryen/src)

# target_link_libraries(prometheus wabt)
target_link_libraries(prometheus binaryen)