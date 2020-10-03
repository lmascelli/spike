cmake_minimum_required(VERSION 3.10)
project(spike LANGUAGES CXX)

set(SPIKE_LIB_SOURCES src/spike_lib.cpp)
add_library(spike_lib ${SPIKE_LIB_SOURCES})