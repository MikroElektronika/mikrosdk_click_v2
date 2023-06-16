cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_presence LANGUAGES MikroC)
else()
    project(lib_presence LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_presence STATIC
        src/presence.c
        include/presence.h
)
add_library(Click.Presence  ALIAS lib_presence)



target_include_directories(lib_presence PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_presence PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_presence PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
