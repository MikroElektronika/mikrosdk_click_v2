cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver8 LANGUAGES MikroC)
else()
    project(lib_leddriver8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver8 STATIC
        src/leddriver8.c
        include/leddriver8.h
)
add_library(Click.LedDriver8  ALIAS lib_leddriver8)



target_include_directories(lib_leddriver8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver8 PUBLIC MikroSDK.Driver)
