cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown13 LANGUAGES MikroC)
else()
    project(lib_stepdown13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown13 STATIC
        src/stepdown13.c
        include/stepdown13.h
)
add_library(Click.StepDown13  ALIAS lib_stepdown13)



target_include_directories(lib_stepdown13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown13 PUBLIC MikroSDK.Driver)

