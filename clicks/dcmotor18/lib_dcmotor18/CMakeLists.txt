cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor18 LANGUAGES MikroC)
else()
    project(lib_dcmotor18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor18 STATIC
        src/dcmotor18.c
        include/dcmotor18.h
)
add_library(Click.DCMotor18  ALIAS lib_dcmotor18)



target_include_directories(lib_dcmotor18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor18 PUBLIC MikroSDK.Driver)
