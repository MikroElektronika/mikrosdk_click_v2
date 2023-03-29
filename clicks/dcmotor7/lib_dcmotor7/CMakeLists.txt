cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor7 LANGUAGES MikroC)
else()
    project(lib_dcmotor7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor7 STATIC
        src/dcmotor7.c
        include/dcmotor7.h
)
add_library(Click.DcMotor7  ALIAS lib_dcmotor7)



target_include_directories(lib_dcmotor7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor7 PUBLIC MikroSDK.Driver)
