cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_matrixrgb LANGUAGES MikroC)
else()
    project(lib_matrixrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_matrixrgb STATIC
        src/matrixrgb.c
        include/matrixrgb.h
)
add_library(Click.MatrixRgb  ALIAS lib_matrixrgb)



target_include_directories(lib_matrixrgb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_matrixrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_matrixrgb PUBLIC MikroSDK.Driver)
