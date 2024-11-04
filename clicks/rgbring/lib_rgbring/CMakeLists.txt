cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rgbring LANGUAGES MikroC)
else()
    project(lib_rgbring LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rgbring STATIC
        src/rgbring.c
        include/rgbring.h
        include/rgbring_delays.h
)
add_library(Click.RGBRing  ALIAS lib_rgbring)



target_include_directories(lib_rgbring PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rgbring PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rgbring PUBLIC MikroSDK.Driver)

