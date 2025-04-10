cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_micropump LANGUAGES MikroC)
else()
    project(lib_micropump LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_micropump STATIC
        src/micropump.c
        include/micropump.h
)
add_library(Click.MicroPump  ALIAS lib_micropump)



target_include_directories(lib_micropump PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_micropump PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_micropump PUBLIC MikroSDK.Driver)

