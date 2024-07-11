cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper23 LANGUAGES MikroC)
else()
    project(lib_stepper23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper23 STATIC
        src/stepper23.c
        include/stepper23.h
)
add_library(Click.Stepper23  ALIAS lib_stepper23)



target_include_directories(lib_stepper23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper23 PUBLIC MikroSDK.Driver)

