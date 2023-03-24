cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_linefollower LANGUAGES MikroC)
else()
    project(lib_linefollower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_linefollower STATIC
        src/linefollower.c
        include/linefollower.h
)
add_library(Click.LineFollower  ALIAS lib_linefollower)



target_include_directories(lib_linefollower PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_linefollower PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_linefollower PUBLIC MikroSDK.Driver)
