cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stepper9 LANGUAGES MikroC)
else()
    project(lib_stepper9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stepper9 STATIC
        src/stepper9.c
        include/stepper9.h
)
add_library(Click.Stepper9  ALIAS lib_stepper9)



target_include_directories(lib_stepper9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stepper9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stepper9 PUBLIC MikroSDK.Driver)
