cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_enocean5 LANGUAGES MikroC)
else()
    project(lib_enocean5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_enocean5 STATIC
        src/enocean5.c
        include/enocean5.h
)
add_library(Click.EnOcean5  ALIAS lib_enocean5)



target_include_directories(lib_enocean5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_enocean5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_enocean5 PUBLIC MikroSDK.Driver)

