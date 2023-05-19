cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor20 LANGUAGES MikroC)
else()
    project(lib_dcmotor20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor20 STATIC
        src/dcmotor20.c
        include/dcmotor20.h
)
add_library(Click.DCMotor20  ALIAS lib_dcmotor20)



target_include_directories(lib_dcmotor20 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor20 PUBLIC MikroSDK.Driver)
