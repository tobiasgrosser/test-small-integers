# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project
project(SmallIntegers)

add_subdirectory(googletest)
add_subdirectory(benchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

# Add a library to this build. The name of the library is MyLibrary and it
# consists of only the MyLibrary.cpp file
add_executable(SmallIntegerBench src/SmallIntegerBench.cpp)
target_link_libraries(SmallIntegerBench benchmark::benchmark)

add_executable(SmallIntegerTest src/SmallIntegerTest.cpp)
target_link_libraries(SmallIntegerTest gtest_main)
