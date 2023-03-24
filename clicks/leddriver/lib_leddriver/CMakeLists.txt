cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver LANGUAGES MikroC)
else()
    project(lib_leddriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver STATIC
        src/leddriver.c
        include/leddriver.h
)
add_library(Click.LedDriver  ALIAS lib_leddriver)



target_include_directories(lib_leddriver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver PUBLIC MikroSDK.Driver)
