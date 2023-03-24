cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2ctocan LANGUAGES MikroC)
else()
    project(lib_i2ctocan LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2ctocan STATIC
        src/i2ctocan.c
        include/i2ctocan.h
)
add_library(Click.I2cToCan  ALIAS lib_i2ctocan)



target_include_directories(lib_i2ctocan PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2ctocan PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2ctocan PUBLIC MikroSDK.Driver)
