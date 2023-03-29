cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rotaryr LANGUAGES MikroC)
else()
    project(lib_rotaryr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rotaryr STATIC
        src/rotaryr.c
        include/rotaryr.h
)
add_library(Click.RotaryR  ALIAS lib_rotaryr)



target_include_directories(lib_rotaryr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rotaryr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rotaryr PUBLIC MikroSDK.Driver)
