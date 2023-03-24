cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost7 LANGUAGES MikroC)
else()
    project(lib_boost7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost7 STATIC
        src/boost7.c
        include/boost7.h
)
add_library(Click.Boost7  ALIAS lib_boost7)



target_include_directories(lib_boost7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost7 PUBLIC MikroSDK.Driver)

