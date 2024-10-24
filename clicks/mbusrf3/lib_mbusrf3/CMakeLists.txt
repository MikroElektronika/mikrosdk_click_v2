cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mbusrf3 LANGUAGES MikroC)
else()
    project(lib_mbusrf3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mbusrf3 STATIC
        src/mbusrf3.c
        include/mbusrf3.h
)
add_library(Click.MBUSRF3  ALIAS lib_mbusrf3)



target_include_directories(lib_mbusrf3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mbusrf3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mbusrf3 PUBLIC MikroSDK.Driver)

