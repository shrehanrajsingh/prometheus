include_directories(../)

add_executable(TEST_EXE test.cpp)
target_link_libraries(TEST_EXE wlang)
add_test(TEST_1 TEST_EXE)