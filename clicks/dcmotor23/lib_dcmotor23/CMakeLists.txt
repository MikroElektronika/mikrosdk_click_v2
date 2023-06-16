cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor23 LANGUAGES MikroC)
else()
    project(lib_dcmotor23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor23 STATIC
        src/dcmotor23.c
        include/dcmotor23.h
)
add_library(Click.DCMotor23  ALIAS lib_dcmotor23)



target_include_directories(lib_dcmotor23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor23 PUBLIC MikroSDK.Driver)

