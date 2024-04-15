cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mosaic LANGUAGES MikroC)
else()
    project(lib_mosaic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mosaic STATIC
        src/mosaic.c
        include/mosaic.h
)
add_library(Click.Mosaic  ALIAS lib_mosaic)



target_include_directories(lib_mosaic PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mosaic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mosaic PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_mosaic PUBLIC MikroSDK.GenericPointer)

