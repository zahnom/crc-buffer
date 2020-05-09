
cmake_minimum_required(VERSION 3.14)
project(crc-buffer)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(googletest)
add_subdirectory(test)