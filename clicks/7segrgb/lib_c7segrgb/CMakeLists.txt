cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7segrgb LANGUAGES MikroC)
else()
    project(lib_c7segrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7segrgb
STATIC
src/c7segrgb.c
include/c7segrgb.h
include/c7segrgb_delays.h
)
add_library(Click.7SegRgb  ALIAS lib_c7segrgb)



target_include_directories(lib_c7segrgb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7segrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7segrgb PUBLIC MikroSDK.Driver)
