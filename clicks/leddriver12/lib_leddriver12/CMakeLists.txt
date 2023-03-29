cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver12 LANGUAGES MikroC)
else()
    project(lib_leddriver12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver12 STATIC
        src/leddriver12.c
        include/leddriver12.h
)
add_library(Click.LEDDriver12  ALIAS lib_leddriver12)



target_include_directories(lib_leddriver12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver12 PUBLIC MikroSDK.Driver)
