cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall12i2c LANGUAGES MikroC)
else()
    project(lib_c3dhall12i2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall12i2c STATIC
        src/c3dhall12i2c.c
        include/c3dhall12i2c.h
)
add_library(Click.3DHall12I2C  ALIAS lib_c3dhall12i2c)



target_include_directories(lib_c3dhall12i2c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall12i2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall12i2c PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
