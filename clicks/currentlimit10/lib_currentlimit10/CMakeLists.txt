cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_currentlimit10 LANGUAGES MikroC)
else()
    project(lib_currentlimit10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_currentlimit10 STATIC
        src/currentlimit10.c
        include/currentlimit10.h
)
add_library(Click.CurrentLimit10  ALIAS lib_currentlimit10)



target_include_directories(lib_currentlimit10 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_currentlimit10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_currentlimit10 PUBLIC MikroSDK.Driver)

