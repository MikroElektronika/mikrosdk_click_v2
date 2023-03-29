cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2ctospi LANGUAGES MikroC)
else()
    project(lib_i2ctospi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2ctospi STATIC
        src/i2ctospi.c
        include/i2ctospi.h
)
add_library(Click.I2cToSpi  ALIAS lib_i2ctospi)



target_include_directories(lib_i2ctospi PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2ctospi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2ctospi PUBLIC MikroSDK.Driver)
