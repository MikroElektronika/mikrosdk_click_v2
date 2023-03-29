cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_matrixg LANGUAGES MikroC)
else()
    project(lib_matrixg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_matrixg STATIC
        src/matrixg.c
        include/matrixg.h
)
add_library(Click.MatrixG  ALIAS lib_matrixg)



target_include_directories(lib_matrixg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_matrixg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_matrixg PUBLIC MikroSDK.Driver)
