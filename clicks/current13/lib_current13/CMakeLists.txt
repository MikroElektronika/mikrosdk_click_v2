cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current13 LANGUAGES MikroC)
else()
    project(lib_current13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current13 STATIC
        src/current13.c
        include/current13.h
)
add_library(Click.Current13  ALIAS lib_current13)



target_include_directories(lib_current13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current13 PUBLIC MikroSDK.Driver)

