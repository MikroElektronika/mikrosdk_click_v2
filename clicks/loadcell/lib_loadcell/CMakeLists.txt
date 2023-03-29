cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell LANGUAGES MikroC)
else()
    project(lib_loadcell LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell STATIC
        src/loadcell.c
        include/loadcell.h
)
add_library(Click.LoadCell  ALIAS lib_loadcell)



target_include_directories(lib_loadcell PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell PUBLIC MikroSDK.Driver)
