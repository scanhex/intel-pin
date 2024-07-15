cmake_minimum_required(VERSION 3.10)
project(IntelPIN)

set(CMAKE_CXX_STANDARD 11)

# Assume PIN_ROOT is set as an environment variable
set(PIN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pin)

# Define the library
add_library(IntelPIN INTERFACE)

# Include directories
target_include_directories(IntelPIN INTERFACE
    ${PIN_ROOT}/source/include/pin
    ${PIN_ROOT}/source/include/pin/gen
    ${PIN_ROOT}/extras/components/include
    ${PIN_ROOT}/extras/xed-intel64/include
    ${PIN_ROOT}/source/tools/Utils
    ${PIN_ROOT}/source/tools/InstLib
)

# Compiler definitions
target_compile_definitions(IntelPIN INTERFACE
    TARGET_IA32E
    HOST_IA32E
    TARGET_LINUX
    BIGARRAY_MULTIPLIER=1
    USING_XED
    _GLIBCXX_USE_CXX11_ABI=0
)

# Compiler options
target_compile_options(IntelPIN INTERFACE
    -Wall
    -Werror
    -Wno-unknown-pragmas
    -fno-stack-protector
    -fno-exceptions
    -funwind-tables
    -fno-rtti
    -fabi-version=2
    -fPIC
    -fomit-frame-pointer
    -fno-strict-aliasing
    -faligned-new
)

# Linker options
target_link_options(IntelPIN INTERFACE
    -Wl,--hash-style=sysv
    -Wl,-Bsymbolic
    -Wl,--version-script=${PIN_ROOT}/source/include/pin/pintool.ver
)

# Libraries
target_link_libraries(IntelPIN INTERFACE
    ${PIN_ROOT}/intel64/runtime/pincrt/crtbeginS.o
    ${PIN_ROOT}/intel64/runtime/pincrt/crtendS.o
    -L${PIN_ROOT}/intel64/runtime/pincrt
    -L${PIN_ROOT}/intel64/lib
    -L${PIN_ROOT}/intel64/lib-ext
    -L${PIN_ROOT}/extras/xed-intel64/lib
    -lc++
    -lpin
    -lxed
    -lpindwarf
    -ldl-dynamic
    -nostdlib
    -lm-dynamic
    -lc-dynamic
    -lunwind-dynamic
)

# Set rpath
set_target_properties(IntelPIN PROPERTIES
    INTERFACE_LINK_OPTIONS "-Wl,-rpath,${PIN_ROOT}/intel64/runtime/pincrt:${PIN_ROOT}/intel64/lib:${PIN_ROOT}/intel64/lib-ext:${PIN_ROOT}/extras/xed-intel64/lib"
)

add_executable(inscount inscount.cpp)
target_link_libraries(inscount IntelPIN)
add_executable(busy_loop busy_loop.cpp)


