cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rotaryb LANGUAGES MikroC)
else()
    project(lib_rotaryb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rotaryb STATIC
        src/rotaryb.c
        include/rotaryb.h
)
add_library(Click.RotaryB  ALIAS lib_rotaryb)



target_include_directories(lib_rotaryb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rotaryb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rotaryb PUBLIC MikroSDK.Driver)
