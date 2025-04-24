cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vref LANGUAGES MikroC)
else()
    project(lib_vref LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vref STATIC
        src/vref.c
        include/vref.h
)
add_library(Click.VREF  ALIAS lib_vref)



target_include_directories(lib_vref PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vref PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vref PUBLIC MikroSDK.Driver)

