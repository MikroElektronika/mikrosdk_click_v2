cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper14 LANGUAGES MikroC)
else()
    project(lib_stepper14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper14 STATIC
        src/stepper14.c
        include/stepper14.h
)
add_library(Click.Stepper14  ALIAS lib_stepper14)



target_include_directories(lib_stepper14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper14 PUBLIC MikroSDK.Driver)

