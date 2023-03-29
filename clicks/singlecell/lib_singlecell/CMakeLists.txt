cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_singlecell LANGUAGES MikroC)
else()
    project(lib_singlecell LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_singlecell STATIC
        src/singlecell.c
        include/singlecell.h
)
add_library(Click.SingleCell  ALIAS lib_singlecell)



target_include_directories(lib_singlecell PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_singlecell PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_singlecell PUBLIC MikroSDK.Driver)
