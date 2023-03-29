cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper11 LANGUAGES MikroC)
else()
    project(lib_stepper11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper11 STATIC
        src/stepper11.c
        include/stepper11.h
)
add_library(Click.Stepper11  ALIAS lib_stepper11)



target_include_directories(lib_stepper11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper11 PUBLIC MikroSDK.Driver)
