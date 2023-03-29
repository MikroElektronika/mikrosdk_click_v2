cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor5 LANGUAGES MikroC)
else()
    project(lib_dcmotor5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor5 STATIC
        src/dcmotor5.c
        include/dcmotor5.h
)
add_library(Click.DcMotor5  ALIAS lib_dcmotor5)



target_include_directories(lib_dcmotor5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor5 PUBLIC MikroSDK.Driver)
