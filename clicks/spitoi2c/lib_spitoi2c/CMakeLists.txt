cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spitoi2c LANGUAGES MikroC)
else()
    project(lib_spitoi2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spitoi2c STATIC
        src/spitoi2c.c
        include/spitoi2c.h
)
add_library(Click.SPItoI2C  ALIAS lib_spitoi2c)

target_include_directories(lib_spitoi2c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spitoi2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spitoi2c PUBLIC MikroSDK.Driver)

