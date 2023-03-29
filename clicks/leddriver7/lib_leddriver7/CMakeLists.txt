cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver7 LANGUAGES MikroC)
else()
    project(lib_leddriver7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver7 STATIC
        src/leddriver7.c
        include/leddriver7.h
)
add_library(Click.LedDriver7  ALIAS lib_leddriver7)



target_include_directories(lib_leddriver7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver7 PUBLIC MikroSDK.Driver)
