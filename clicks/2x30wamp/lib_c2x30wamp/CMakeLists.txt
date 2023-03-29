cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c2x30wamp LANGUAGES MikroC)
else()
    project(lib_c2x30wamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c2x30wamp STATIC
        src/c2x30wamp.c
        include/c2x30wamp.h
)
add_library(Click.2x30wAmp  ALIAS lib_c2x30wamp)



target_include_directories(lib_c2x30wamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c2x30wamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c2x30wamp PUBLIC MikroSDK.Driver)
