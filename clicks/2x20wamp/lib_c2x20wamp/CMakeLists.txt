cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c2x20wamp LANGUAGES MikroC)
else()
    project(lib_c2x20wamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c2x20wamp STATIC
        src/c2x20wamp.c
        include/c2x20wamp.h
)
add_library(Click.2x20WAmp  ALIAS lib_c2x20wamp)



target_include_directories(lib_c2x20wamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c2x20wamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c2x20wamp PUBLIC MikroSDK.Driver)
