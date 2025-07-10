cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ism8 LANGUAGES MikroC)
else()
    project(lib_ism8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ism8 STATIC
        src/ism8.c
        include/ism8.h
)
add_library(Click.ISM8  ALIAS lib_ism8)



target_include_directories(lib_ism8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ism8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ism8 PUBLIC MikroSDK.Driver)

