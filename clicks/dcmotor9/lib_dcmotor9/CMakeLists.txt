cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor9 LANGUAGES MikroC)
else()
    project(lib_dcmotor9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor9 STATIC
        src/dcmotor9.c
        include/dcmotor9.h
)
add_library(Click.DcMotor9  ALIAS lib_dcmotor9)



target_include_directories(lib_dcmotor9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor9 PUBLIC MikroSDK.Driver)
