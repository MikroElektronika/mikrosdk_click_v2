cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lsm303agr LANGUAGES MikroC)
else()
    project(lib_lsm303agr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lsm303agr STATIC
        src/lsm303agr.c
        include/lsm303agr.h
)
add_library(Click.LSM303AGR  ALIAS lib_lsm303agr)



target_include_directories(lib_lsm303agr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lsm303agr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lsm303agr PUBLIC MikroSDK.Driver)
