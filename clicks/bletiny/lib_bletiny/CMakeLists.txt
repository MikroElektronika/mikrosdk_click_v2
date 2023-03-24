cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bletiny LANGUAGES MikroC)
else()
    project(lib_bletiny LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bletiny STATIC
        src/bletiny.c
        include/bletiny.h
)
add_library(Click.BLETINY  ALIAS lib_bletiny)



target_include_directories(lib_bletiny PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bletiny PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bletiny PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_bletiny PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_bletiny PUBLIC MikroSDK.GenericPointer)
