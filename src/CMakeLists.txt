cmake_minimum_required(VERSION 3.12)
project(strace2seccomp LANGUAGES CXX)

set(st2se_VERSION_MAJOR 1)
set(st2se_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wsuggest-override  -Wnull-dereference -Wshadow -Wold-style-cast -pedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address,undefined -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -flto -DNDEBUG")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

# Binary dependencies
add_library(algorithm algorithm.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm)

add_library(algorithm_strict algorithm_strict.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_strict)

add_library(algorithm_advanced algorithm_advanced.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_advanced)
target_link_libraries(algorithm_advanced algorithm)

add_library(algorithm_weak algorithm_weak.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} algorithm_weak)
target_link_libraries(algorithm_weak algorithm)

add_library(argparse argparse.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} argparse)

add_library(format format.cc)
set (EXTRA_LIBS ${EXTRA_LIBS} format)

add_library(posix posix.cc)
set (EXTRA_LIBS ${EXTRA_LIBS} posix)

add_library(generator generator.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} generator)

add_library(ids ids.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} ids)

add_library(optimizer optimizer.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} optimizer)

add_library(output output.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} output)
target_link_libraries(output posix format)

add_library(outputCPP outputCPP.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} outputCPP)
target_link_libraries(outputCPP output)

add_library(StraceParser straceparser.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} StraceParser)

add_library(states states.cpp)
set (EXTRA_LIBS ${EXTRA_LIBS} states)

add_executable(strace2seccomp main.cpp)

target_link_libraries(strace2seccomp ${EXTRA_LIBS})

#Test binary dependencies
add_library(ids_test ids_test.cpp)
set (TEST_LIBS ${TEST_LIBS} ids_test)
target_link_libraries(ids_test ids)

add_library(outputCPP_test outputCPP_test.cpp)
set (TEST_LIBS ${TEST_LIBS} outputCPP_test)
target_link_libraries(outputCPP_test outputCPP)

add_library(argparse_test argparse_test.cpp)
set (TEST_LIBS ${TEST_LIBS} argparse_test)
target_link_libraries(argparse_test argparse)

add_library(generator_test generator_test.cpp)
set (TEST_LIBS ${TEST_LIBS} generator_test)
target_link_libraries(generator_test generator)


add_library(states_test states_test.cpp)
set (TEST_LIBS ${TEST_LIBS} states_test)
target_link_libraries(states_test states)

add_executable(st2se-test test_main.cpp)
target_link_libraries(st2se-test ${TEST_LIBS} ${EXTRA_LIBS})
add_custom_target(check st2se-test)

#astyle recipe
add_custom_target(astyle DEPENDS astylerc)
add_custom_command(
  TARGET   astyle
  COMMAND  "./astyle_script.sh"
)

include(CTest)
add_test(MainTest st2se-test)