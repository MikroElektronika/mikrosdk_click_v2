cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper16 LANGUAGES MikroC)
else()
    project(lib_stepper16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper16 STATIC
        src/stepper16.c
        include/stepper16.h
)
add_library(Click.Stepper16  ALIAS lib_stepper16)



target_include_directories(lib_stepper16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper16 PUBLIC MikroSDK.Driver)
