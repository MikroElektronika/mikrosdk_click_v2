cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor28fng LANGUAGES MikroC)
else()
    project(lib_dcmotor28fng LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor28fng STATIC
        src/dcmotor28fng.c
        include/dcmotor28fng.h
)
add_library(Click.DCMotor28FNG  ALIAS lib_dcmotor28fng)



target_include_directories(lib_dcmotor28fng PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor28fng PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor28fng PUBLIC MikroSDK.Driver)

