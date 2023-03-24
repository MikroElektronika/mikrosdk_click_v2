cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver13 LANGUAGES MikroC)
else()
    project(lib_leddriver13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver13 STATIC
        src/leddriver13.c
        include/leddriver13.h
)
add_library(Click.LEDDriver13  ALIAS lib_leddriver13)



target_include_directories(lib_leddriver13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver13 PUBLIC MikroSDK.Driver)
