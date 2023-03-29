cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uart1wire LANGUAGES MikroC)
else()
    project(lib_uart1wire LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uart1wire STATIC
        src/uart1wire.c
        include/uart1wire.h
)
add_library(Click.UART1Wire  ALIAS lib_uart1wire)



target_include_directories(lib_uart1wire PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uart1wire PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uart1wire PUBLIC MikroSDK.Driver)
