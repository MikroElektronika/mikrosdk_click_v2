cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor LANGUAGES MikroC)
else()
    project(lib_dcmotor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor STATIC
        src/dcmotor.c
        include/dcmotor.h
)
add_library(Click.DcMotor  ALIAS lib_dcmotor)



target_include_directories(lib_dcmotor PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor PUBLIC MikroSDK.Driver)
