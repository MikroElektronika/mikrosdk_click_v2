cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper LANGUAGES MikroC)
else()
    project(lib_stepper LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper STATIC
        src/stepper.c
        include/stepper.h
)
add_library(Click.Stepper  ALIAS lib_stepper)



target_include_directories(lib_stepper PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper PUBLIC MikroSDK.Driver)

