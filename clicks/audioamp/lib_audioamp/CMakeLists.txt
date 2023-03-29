cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp LANGUAGES MikroC)
else()
    project(lib_audioamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp STATIC
        src/audioamp.c
        include/audioamp.h
)
add_library(Click.AudioAmp  ALIAS lib_audioamp)



target_include_directories(lib_audioamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp PUBLIC MikroSDK.Driver)
