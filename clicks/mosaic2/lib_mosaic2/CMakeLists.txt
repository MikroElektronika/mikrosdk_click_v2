cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mosaic2 LANGUAGES MikroC)
else()
    project(lib_mosaic2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mosaic2 STATIC
        src/mosaic2.c
        include/mosaic2.h
)
add_library(Click.Mosaic2  ALIAS lib_mosaic2)



target_include_directories(lib_mosaic2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mosaic2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mosaic2 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_mosaic2 PUBLIC MikroSDK.GenericPointer)

