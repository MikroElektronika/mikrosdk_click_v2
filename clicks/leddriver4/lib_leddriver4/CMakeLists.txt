cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver4 LANGUAGES MikroC)
else()
    project(lib_leddriver4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver4 STATIC
        src/leddriver4.c
        include/leddriver4.h
)
add_library(Click.LedDriver4  ALIAS lib_leddriver4)



target_include_directories(lib_leddriver4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver4 PUBLIC MikroSDK.Driver)
