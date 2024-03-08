cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper13 LANGUAGES MikroC)
else()
    project(lib_stepper13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper13 STATIC
        src/stepper13.c
        include/stepper13.h
)
add_library(Click.Stepper13  ALIAS lib_stepper13)



target_include_directories(lib_stepper13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper13 PUBLIC MikroSDK.Driver)

