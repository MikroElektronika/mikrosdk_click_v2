cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor3 LANGUAGES MikroC)
else()
    project(lib_dcmotor3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor3 STATIC
        src/dcmotor3.c
        include/dcmotor3.h
)
add_library(Click.DcMotor3  ALIAS lib_dcmotor3)



target_include_directories(lib_dcmotor3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor3 PUBLIC MikroSDK.Driver)
