cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_shutter LANGUAGES MikroC)
else()
    project(lib_shutter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_shutter STATIC
        src/shutter.c
        include/shutter.h
)
add_library(Click.Shutter  ALIAS lib_shutter)



target_include_directories(lib_shutter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_shutter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_shutter PUBLIC MikroSDK.Driver)
