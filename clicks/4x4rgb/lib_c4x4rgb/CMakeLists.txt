cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4x4rgb LANGUAGES MikroC)
else()
    project(lib_c4x4rgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4x4rgb STATIC
        src/c4x4rgb.c
        include/c4x4rgb.h
)
add_library(Click.4x4Rgb  ALIAS lib_c4x4rgb)



target_include_directories(lib_c4x4rgb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4x4rgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4x4rgb PUBLIC MikroSDK.Driver)
