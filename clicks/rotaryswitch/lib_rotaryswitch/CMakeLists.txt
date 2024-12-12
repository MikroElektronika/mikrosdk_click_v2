cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rotaryswitch LANGUAGES MikroC)
else()
    project(lib_rotaryswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rotaryswitch STATIC
        src/rotaryswitch.c
        include/rotaryswitch.h
)
add_library(Click.RotarySwitch  ALIAS lib_rotaryswitch)



target_include_directories(lib_rotaryswitch PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rotaryswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rotaryswitch PUBLIC MikroSDK.Driver)

