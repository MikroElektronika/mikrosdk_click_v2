cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper2 LANGUAGES MikroC)
else()
    project(lib_stepper2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper2 STATIC
        src/stepper2.c
        include/stepper2.h
)
add_library(Click.Stepper2  ALIAS lib_stepper2)



target_include_directories(lib_stepper2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper2 PUBLIC MikroSDK.Driver)

