cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor10 LANGUAGES MikroC)
else()
    project(lib_dcmotor10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor10 STATIC
        src/dcmotor10.c
        include/dcmotor10.h
)
add_library(Click.DcMotor10  ALIAS lib_dcmotor10)



target_include_directories(lib_dcmotor10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor10 PUBLIC MikroSDK.Driver)
