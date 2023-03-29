cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor4 LANGUAGES MikroC)
else()
    project(lib_dcmotor4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor4 STATIC
        src/dcmotor4.c
        include/dcmotor4.h
)
add_library(Click.DcMotor4  ALIAS lib_dcmotor4)



target_include_directories(lib_dcmotor4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor4 PUBLIC MikroSDK.Driver)
