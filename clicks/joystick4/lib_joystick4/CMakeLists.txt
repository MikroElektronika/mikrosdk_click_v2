cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_joystick4 LANGUAGES MikroC)
else()
    project(lib_joystick4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_joystick4 STATIC
        src/joystick4.c
        include/joystick4.h
)
add_library(Click.Joystick4  ALIAS lib_joystick4)



target_include_directories(lib_joystick4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_joystick4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_joystick4 PUBLIC MikroSDK.Driver)

