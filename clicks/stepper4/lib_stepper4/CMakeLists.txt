cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper4 LANGUAGES MikroC)
else()
    project(lib_stepper4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper4 STATIC
        src/stepper4.c
        include/stepper4.h
)
add_library(Click.Stepper4  ALIAS lib_stepper4)



target_include_directories(lib_stepper4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper4 PUBLIC MikroSDK.Driver)

