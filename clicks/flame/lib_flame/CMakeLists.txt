cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flame LANGUAGES MikroC)
else()
    project(lib_flame LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flame STATIC
        src/flame.c
        include/flame.h
)
add_library(Click.Flame  ALIAS lib_flame)



target_include_directories(lib_flame PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flame PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flame PUBLIC MikroSDK.Driver)
