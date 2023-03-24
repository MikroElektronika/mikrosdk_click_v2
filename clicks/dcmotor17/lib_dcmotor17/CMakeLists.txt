cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor17 LANGUAGES MikroC)
else()
    project(lib_dcmotor17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor17 STATIC
        src/dcmotor17.c
        include/dcmotor17.h
)
add_library(Click.DcMotor17  ALIAS lib_dcmotor17)



target_include_directories(lib_dcmotor17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor17 PUBLIC MikroSDK.Driver)
