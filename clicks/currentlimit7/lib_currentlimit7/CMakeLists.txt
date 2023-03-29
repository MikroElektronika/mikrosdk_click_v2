cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_currentlimit7 LANGUAGES MikroC)
else()
    project(lib_currentlimit7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_currentlimit7 STATIC
        src/currentlimit7.c
        include/currentlimit7.h
)
add_library(Click.CurrentLimit7  ALIAS lib_currentlimit7)



target_include_directories(lib_currentlimit7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_currentlimit7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_currentlimit7 PUBLIC MikroSDK.Driver)
