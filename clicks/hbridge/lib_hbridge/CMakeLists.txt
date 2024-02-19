cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge LANGUAGES MikroC)
else()
    project(lib_hbridge LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge STATIC
        src/hbridge.c
        include/hbridge.h
)
add_library(Click.HBridge  ALIAS lib_hbridge)



target_include_directories(lib_hbridge PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge PUBLIC MikroSDK.Driver)

