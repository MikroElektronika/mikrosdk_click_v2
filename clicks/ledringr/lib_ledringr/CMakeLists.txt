cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledringr LANGUAGES MikroC)
else()
    project(lib_ledringr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledringr STATIC
        src/ledringr.c
        include/ledringr.h
)
add_library(Click.LedringR  ALIAS lib_ledringr)



target_include_directories(lib_ledringr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledringr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledringr PUBLIC MikroSDK.Driver)
