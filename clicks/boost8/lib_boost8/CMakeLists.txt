cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost8 LANGUAGES MikroC)
else()
    project(lib_boost8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost8 STATIC
        src/boost8.c
        include/boost8.h
)
add_library(Click.Boost8  ALIAS lib_boost8)



target_include_directories(lib_boost8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost8 PUBLIC MikroSDK.Driver)
