cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell8 LANGUAGES MikroC)
else()
    project(lib_loadcell8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell8 STATIC
        src/loadcell8.c
        include/loadcell8.h
)
add_library(Click.LoadCell8  ALIAS lib_loadcell8)



target_include_directories(lib_loadcell8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell8 PUBLIC MikroSDK.Driver)

