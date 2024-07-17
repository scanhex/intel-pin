cmake_minimum_required(VERSION 3.10)
project(IntelPIN)

set(CMAKE_CXX_STANDARD 20)

set(PIN_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pin)

# Define the library
add_library(IntelPIN INTERFACE)

set(BIONIC_ARCH x86_64)

# Include directories
target_include_directories(IntelPIN INTERFACE
    ${PIN_ROOT}/source/include/pin
    ${PIN_ROOT}/source/include/pin/gen
    ${PIN_ROOT}/extras/components/include
    ${PIN_ROOT}/extras/xed-intel64/include
    ${PIN_ROOT}/extras/xed-intel64/include/xed
    ${PIN_ROOT}/source/tools/Utils
    ${PIN_ROOT}/source/tools/InstLib
    SYSTEM ${PIN_ROOT}/extras/cxx/include
    SYSTEM ${PIN_ROOT}/extras/crt/include
    SYSTEM ${PIN_ROOT}/extras/crt/include/arch-${BIONIC_ARCH}
    SYSTEM ${PIN_ROOT}/extras/crt/include/kernel/uapi
    SYSTEM ${PIN_ROOT}/extras/crt/include/kernel/uapi/asm-x86
)

# Compiler definitions
target_compile_definitions(IntelPIN INTERFACE
    TARGET_IA32E
    HOST_IA32E
    TARGET_LINUX
    PIN_CRT=1
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

# Libraries
target_link_libraries(IntelPIN INTERFACE
    ${PIN_ROOT}/intel64/runtime/pincrt/crtbeginS.o
    ${PIN_ROOT}/intel64/runtime/pincrt/crtendS.o
    -L${PIN_ROOT}/intel64/runtime/pincrt
    -L${PIN_ROOT}/intel64/lib
    -L${PIN_ROOT}/intel64/lib-ext
    -L${PIN_ROOT}/extras/xed-intel64/lib
    -nostdlib
    -lc++
    -lc++abi 
    -lpin
    -lxed
    -lpindwarf
    -ldl-dynamic
    -lm-dynamic
    -lc-dynamic
    -lunwind-dynamic
    -Wl,--hash-style=sysv
    #    -Wl,-Bsymbolic - try enabling if any issues arise
    -Wl,--version-script=${PIN_ROOT}/source/include/pin/pintool.ver
)

add_library(inscount SHARED inscount.cpp)
target_link_libraries(inscount IntelPIN)
add_executable(busy_loop busy_loop.cpp)


