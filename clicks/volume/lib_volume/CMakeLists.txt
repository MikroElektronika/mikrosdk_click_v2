cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_volume LANGUAGES MikroC)
else()
    project(lib_volume LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_volume STATIC
        src/volume.c
        include/volume.h
)
add_library(Click.Volume  ALIAS lib_volume)



target_include_directories(lib_volume PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_volume PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_volume PUBLIC MikroSDK.Driver)
