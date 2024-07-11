cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper24 LANGUAGES MikroC)
else()
    project(lib_stepper24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper24 STATIC
        src/stepper24.c
        include/stepper24.h
)
add_library(Click.Stepper24  ALIAS lib_stepper24)



target_include_directories(lib_stepper24 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper24 PUBLIC MikroSDK.Driver)

