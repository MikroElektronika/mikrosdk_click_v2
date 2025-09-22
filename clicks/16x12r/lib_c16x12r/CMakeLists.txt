cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c16x12r LANGUAGES MikroC)
else()
    project(lib_c16x12r LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c16x12r
STATIC
src/c16x12r.c
include/c16x12r.h
include/c16x12r_resources.h
src/c16x12r_resources.c
)
add_library(Click.16x12R  ALIAS lib_c16x12r)



target_include_directories(lib_c16x12r PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c16x12r PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c16x12r PUBLIC MikroSDK.Driver)

