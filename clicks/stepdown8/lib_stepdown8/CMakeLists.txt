cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepdown8 LANGUAGES MikroC)
else()
    project(lib_stepdown8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepdown8 STATIC
        src/stepdown8.c
        include/stepdown8.h
)
add_library(Click.StepDown8  ALIAS lib_stepdown8)



target_include_directories(lib_stepdown8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepdown8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepdown8 PUBLIC MikroSDK.Driver)

