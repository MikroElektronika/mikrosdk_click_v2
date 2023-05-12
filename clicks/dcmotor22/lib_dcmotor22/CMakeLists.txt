cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor22 LANGUAGES MikroC)
else()
    project(lib_dcmotor22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor22 STATIC
        src/dcmotor22.c
        include/dcmotor22.h
)
add_library(Click.DCMotor22  ALIAS lib_dcmotor22)



target_include_directories(lib_dcmotor22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor22 PUBLIC MikroSDK.Driver)
