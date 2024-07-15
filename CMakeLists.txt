cmake_minimum_required(VERSION 3.10)
project(PinTool)

set(CMAKE_CXX_STANDARD 11)

# Path to the Intel PIN installation
set(PIN_DIR "${CMAKE_SOURCE_DIR}/pin")

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(SEND_ERROR "This CMakeLists.txt only supports 64-bit builds.")
endif()

# Loosely based on ${PIN_DIR}/source/tools/Config/makefile.win.config
set(PIN_EXE "${PIN_DIR}/intel64/bin/pin${CMAKE_EXECUTABLE_SUFFIX}")

string(REGEX REPLACE "/" "\\\\" PIN_EXE ${PIN_EXE})

add_library(IntelPIN INTERFACE)

set(BIONIC_ARCH "x86_64")

target_include_directories(IntelPIN INTERFACE
    ${PIN_DIR}/extras/crt/include/arch-${BIONIC_ARCH} 
    ${PIN_DIR}/source/include/pin
    ${PIN_DIR}/source/include/pin/gen
    ${PIN_DIR}/extras/components/include
    ${PIN_DIR}/extras/stlport/include
    ${PIN_DIR}/extras
    ${PIN_DIR}/extras/libstdc++/include
    ${PIN_DIR}/extras/cxx/include
    ${PIN_DIR}/extras/crt/include
    ${PIN_DIR}/extras/crt
    ${PIN_DIR}/extras/crt/include/kernel/uapi
    ${PIN_DIR}/extras/crt/include/kernel/uapi/asm-x86
)

target_link_libraries(IntelPIN INTERFACE
    pin
    xed
)

#target_link_options(IntelPIN INTERFACE /NODEFAULTLIB /EXPORT:main /BASE:0xC5000000 /ENTRY:Ptrace_DllMainCRTStartup /IGNORE:4210 /IGNORE:4281)
#target_link_options(IntelPIN INTERFACE -nostdlib)
target_link_options(IntelPIN INTERFACE -nostdlib -lc++ -lc++abi -lm-dynamic -lc-dynamic -lunwind-dynamic)


#target_compile_options(IntelPIN INTERFACE /GR- /GS- /EHs- /EHa- /fp:strict /Oi- /FIinclude/msvc_compat.h /wd5208)

target_include_directories(IntelPIN INTERFACE
    ${PIN_DIR}/extras/xed-intel64/include/xed
    ${PIN_DIR}/extras/crt/include/arch-x86_64
)
target_link_directories(IntelPIN INTERFACE
    ${PIN_DIR}/intel64/lib
    ${PIN_DIR}/intel64/lib-ext
    ${PIN_DIR}/intel64/runtime/pincrt
    ${PIN_DIR}/extras/xed-intel64/lib
)
target_compile_definitions(IntelPIN INTERFACE
    TARGET_IA32E
    HOST_IA32E
    TARGET_LINUX
    __PIN__=1
    PIN_CRT=1
    __LP64__
    FUND_TC_TARGETOS=FUND_OS_LINUX
    FUND_TC_HOSTOS=FUND_OS_LINUX
    #_WINDOWS_H_PATH_=../um # dirty hack
)
target_link_libraries(IntelPIN INTERFACE
    #    ntdll-64
    #    kernel32
    ${PIN_DIR}/intel64/runtime/pincrt/crtbeginS.o
)

add_executable(inscount inscount.cpp)
target_link_libraries(inscount IntelPIN)
add_executable(busy_loop busy_loop.cpp)
#target_link_libraries(inscount pin pincrt)
