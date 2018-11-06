cmake_minimum_required(VERSION 3.12)
project(strace2seccomp)


add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wsuggest-override )
add_compile_options(-Wnull-dereference)
add_compile_options(-Wshadow)
add_compile_options(-Wold-style-cast)
add_compile_options(-pedantic)
add_compile_options(-std=c++17)

set(st2se_VERSION_MAJOR 1)
set(st2se_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")


add_library(algorithm algorithm.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm)

add_library(algorithm_strict algorithm_strict.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_strict)

add_library(algorithm_advanced algorithm_advanced.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_advanced)

add_library(algorithm_weak algorithm_weak.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_weak)

add_library(argparse argparse.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} argparse)

add_library(format format.cc)
set (EXTRA_LIBS ${EXTRA_LIBS} format)

add_library(generator generator.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} generator)

add_library(ids ids.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} ids)

add_library(optimizer optimizer.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} optimizer)

add_library(output output.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} output)

add_library(outputCPP outputCPP.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} outputCPP)

add_library(posix posix.cc)
set (EXTRA_LIBS ${EXTRA_LIBS} posix)

add_library(StraceParser straceparser.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} StraceParser)

add_library(states states.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} states)

add_executable(st2se main.cpp)

target_link_libraries(st2se ${EXTRA_LIBS})