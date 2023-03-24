cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stereoamp LANGUAGES MikroC)
else()
    project(lib_stereoamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stereoamp STATIC
        src/stereoamp.c
        include/stereoamp.h
)
add_library(Click.StereoAmp  ALIAS lib_stereoamp)



target_include_directories(lib_stereoamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stereoamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stereoamp PUBLIC MikroSDK.Driver)
