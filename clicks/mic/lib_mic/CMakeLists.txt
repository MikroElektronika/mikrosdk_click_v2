cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic LANGUAGES MikroC)
else()
    project(lib_mic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic STATIC
        src/mic.c
        include/mic.h
)
add_library(Click.Mic  ALIAS lib_mic)



target_include_directories(lib_mic PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic PUBLIC MikroSDK.Driver)
