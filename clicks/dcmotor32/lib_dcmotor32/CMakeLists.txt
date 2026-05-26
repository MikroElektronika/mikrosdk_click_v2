cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor32 LANGUAGES MikroC)
else()
    project(lib_dcmotor32 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor32 STATIC
        src/dcmotor32.c
        include/dcmotor32.h
)
add_library(Click.DCMotor32  ALIAS lib_dcmotor32)


target_include_directories(lib_dcmotor32 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor32 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor32 PUBLIC MikroSDK.Driver)

