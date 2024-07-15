cmake_minimum_required(VERSION 3.10)
project(PinTool)

set(CMAKE_CXX_STANDARD 11)

# Path to the Intel PIN installation
set(PIN_ROOT "/path/to/pin")

include_directories(${PIN_ROOT}/source/include/pin)
include_directories(${PIN_ROOT}/source/include/pin/gen)
include_directories(${PIN_ROOT}/extras/stlport/include)
include_directories(${PIN_ROOT}/extras/libstdc++/include)
include_directories(${PIN_ROOT}/extras/crt/include)

link_directories(${PIN_ROOT}/intel64/lib)
link_directories(${PIN_ROOT}/intel64/lib-ext)

add_executable(inscount inscount.cpp)
target_link_libraries(inscount pin pincrt)