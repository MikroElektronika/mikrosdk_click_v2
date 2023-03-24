cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_linhall LANGUAGES MikroC)
else()
    project(lib_linhall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_linhall STATIC
        src/linhall.c
        include/linhall.h
)
add_library(Click.LinHall  ALIAS lib_linhall)



target_include_directories(lib_linhall PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_linhall PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_linhall PUBLIC MikroSDK.Driver)
