cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_environment4 LANGUAGES MikroC)
else()
    project(lib_environment4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_environment4
STATIC
src/environment4.c
src/sensirion_gas_index_algorithm.c
include/environment4.h
include/sensirion_gas_index_algorithm.h
)
add_library(Click.Environment4  ALIAS lib_environment4)



target_include_directories(lib_environment4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_environment4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_environment4 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})

