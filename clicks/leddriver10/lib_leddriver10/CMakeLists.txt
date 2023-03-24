cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver10 LANGUAGES MikroC)
else()
    project(lib_leddriver10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver10 STATIC
        src/leddriver10.c
        include/leddriver10.h
)
add_library(Click.LEDDriver10  ALIAS lib_leddriver10)



target_include_directories(lib_leddriver10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver10 PUBLIC MikroSDK.Driver)
