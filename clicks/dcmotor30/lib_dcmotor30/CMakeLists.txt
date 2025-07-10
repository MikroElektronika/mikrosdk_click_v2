cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor30 LANGUAGES MikroC)
else()
    project(lib_dcmotor30 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor30 STATIC
        src/dcmotor30.c
        include/dcmotor30.h
)
add_library(Click.DCMotor30  ALIAS lib_dcmotor30)



target_include_directories(lib_dcmotor30 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor30 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor30 PUBLIC MikroSDK.Driver)

