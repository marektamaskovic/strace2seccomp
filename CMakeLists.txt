cmake_minimum_required(VERSION 3.12)
project(strace2seccomp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/include)
include_directories(src/include/catch2)
include_directories(src/include/fmt)
include_directories(src/include/tao)
include_directories(src/include/tao/pegtl)

add_subdirectory(src)
