cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flicker LANGUAGES MikroC)
else()
    project(lib_flicker LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flicker STATIC
        src/flicker.c
        include/flicker.h
)
add_library(Click.Flicker  ALIAS lib_flicker)



target_include_directories(lib_flicker PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flicker PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flicker PUBLIC MikroSDK.Driver)
