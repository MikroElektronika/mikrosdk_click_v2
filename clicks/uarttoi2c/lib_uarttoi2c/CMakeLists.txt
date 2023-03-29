cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uarttoi2c LANGUAGES MikroC)
else()
    project(lib_uarttoi2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uarttoi2c STATIC
        src/uarttoi2c.c
        include/uarttoi2c.h
)
add_library(Click.UARTtoI2C  ALIAS lib_uarttoi2c)



target_include_directories(lib_uarttoi2c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uarttoi2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uarttoi2c PUBLIC MikroSDK.Driver)

