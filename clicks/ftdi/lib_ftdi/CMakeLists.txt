cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ftdi LANGUAGES MikroC)
else()
    project(lib_ftdi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ftdi STATIC
        src/ftdi.c
        include/ftdi.h
)
add_library(Click.FTDI  ALIAS lib_ftdi)



target_include_directories(lib_ftdi PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ftdi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ftdi PUBLIC MikroSDK.Driver)

