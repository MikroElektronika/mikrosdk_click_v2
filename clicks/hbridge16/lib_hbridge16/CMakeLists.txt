cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge16 LANGUAGES MikroC)
else()
    project(lib_hbridge16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge16 STATIC
        src/hbridge16.c
        include/hbridge16.h
)
add_library(Click.HBridge16  ALIAS lib_hbridge16)



target_include_directories(lib_hbridge16 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge16 PUBLIC MikroSDK.Driver)

