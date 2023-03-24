cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver5 LANGUAGES MikroC)
else()
    project(lib_leddriver5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver5 STATIC
        src/leddriver5.c
        include/leddriver5.h
)
add_library(Click.LedDriver5  ALIAS lib_leddriver5)



target_include_directories(lib_leddriver5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver5 PUBLIC MikroSDK.Driver)
