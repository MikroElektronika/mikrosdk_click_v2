cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor11 LANGUAGES MikroC)
else()
    project(lib_dcmotor11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor11 STATIC
        src/dcmotor11.c
        include/dcmotor11.h
)
add_library(Click.DcMotor11  ALIAS lib_dcmotor11)



target_include_directories(lib_dcmotor11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor11 PUBLIC MikroSDK.Driver)
