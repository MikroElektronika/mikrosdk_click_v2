cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c8x8r LANGUAGES MikroC)
else()
    project(lib_c8x8r LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c8x8r STATIC
        src/c8x8r.c
        include/c8x8r.h
)
add_library(Click.8x8R  ALIAS lib_c8x8r)



target_include_directories(lib_c8x8r PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c8x8r PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c8x8r PUBLIC MikroSDK.Driver)
