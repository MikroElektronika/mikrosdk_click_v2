cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c2x5wamp LANGUAGES MikroC)
else()
    project(lib_c2x5wamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c2x5wamp STATIC
        src/c2x5wamp.c
        include/c2x5wamp.h
)
add_library(Click.2x5WAmp  ALIAS lib_c2x5wamp)



target_include_directories(lib_c2x5wamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c2x5wamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c2x5wamp PUBLIC MikroSDK.Driver)
