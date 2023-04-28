cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor25 LANGUAGES MikroC)
else()
    project(lib_dcmotor25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor25 STATIC
        src/dcmotor25.c
        include/dcmotor25.h
)
add_library(Click.DCMotor25  ALIAS lib_dcmotor25)



target_include_directories(lib_dcmotor25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor25 PUBLIC MikroSDK.Driver)

