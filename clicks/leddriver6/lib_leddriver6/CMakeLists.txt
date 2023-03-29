cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver6 LANGUAGES MikroC)
else()
    project(lib_leddriver6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver6 STATIC
        src/leddriver6.c
        include/leddriver6.h
)
add_library(Click.Leddriver6  ALIAS lib_leddriver6)



target_include_directories(lib_leddriver6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver6 PUBLIC MikroSDK.Driver)
