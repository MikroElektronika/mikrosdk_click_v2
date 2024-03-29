cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper19 LANGUAGES MikroC)
else()
    project(lib_stepper19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper19 STATIC
        src/stepper19.c
        include/stepper19.h
)
add_library(Click.Stepper19  ALIAS lib_stepper19)



target_include_directories(lib_stepper19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper19 PUBLIC MikroSDK.Driver)

