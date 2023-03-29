cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper18 LANGUAGES MikroC)
else()
    project(lib_stepper18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper18 STATIC
        src/stepper18.c
        include/stepper18.h
)
add_library(Click.Stepper18  ALIAS lib_stepper18)



target_include_directories(lib_stepper18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper18 PUBLIC MikroSDK.Driver)
