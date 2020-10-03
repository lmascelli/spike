cmake_minimum_required(VERSION 3.10)
project(spike LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(SPIKE_LIB_SOURCES src/spike_lib.cpp)
add_library(spike_lib ${SPIKE_LIB_SOURCES})

add_executable(test test/src/test.cpp)
target_include_directories(test PUBLIC src)
target_link_libraries(test spike_lib)