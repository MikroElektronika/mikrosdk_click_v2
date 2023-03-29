cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor21 LANGUAGES MikroC)
else()
    project(lib_dcmotor21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor21 STATIC
        src/dcmotor21.c
        include/dcmotor21.h
)
add_library(Click.DCMotor21  ALIAS lib_dcmotor21)



target_include_directories(lib_dcmotor21 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor21 PUBLIC MikroSDK.Driver)
