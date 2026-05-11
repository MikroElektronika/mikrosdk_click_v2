cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat15eu LANGUAGES MikroC)
else()
    project(lib_ltecat15eu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat15eu STATIC
        src/ltecat15eu.c
        include/ltecat15eu.h
)
add_library(Click.LTECat15EU  ALIAS lib_ltecat15eu)



target_include_directories(lib_ltecat15eu PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat15eu PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat15eu PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_ltecat15eu PUBLIC MikroSDK.Conversions)

