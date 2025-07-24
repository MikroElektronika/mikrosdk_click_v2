cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper27 LANGUAGES MikroC)
else()
    project(lib_stepper27 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper27 STATIC
        src/stepper27.c
        include/stepper27.h
)
add_library(Click.Stepper27  ALIAS lib_stepper27)



target_include_directories(lib_stepper27 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper27 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper27 PUBLIC MikroSDK.Driver)

