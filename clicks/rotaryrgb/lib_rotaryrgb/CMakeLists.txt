cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rotaryrgb LANGUAGES MikroC)
else()
    project(lib_rotaryrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rotaryrgb
STATIC
src/rotaryrgb.c
include/rotaryrgb.h
include/rotaryrgb_delays.h
)
add_library(Click.RotaryRGB  ALIAS lib_rotaryrgb)



target_include_directories(lib_rotaryrgb PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rotaryrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rotaryrgb PUBLIC MikroSDK.Driver)

