cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ninab416 LANGUAGES MikroC)
else()
    project(lib_ninab416 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ninab416 STATIC
        src/ninab416.c
        include/ninab416.h
)
add_library(Click.NINAB416  ALIAS lib_ninab416)



target_include_directories(lib_ninab416 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ninab416 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ninab416 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_ninab416 PUBLIC MikroSDK.GenericPointer)

