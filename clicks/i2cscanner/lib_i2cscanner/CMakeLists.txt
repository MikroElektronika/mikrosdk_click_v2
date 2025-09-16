cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cscanner LANGUAGES MikroC)
else()
    project(lib_i2cscanner LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cscanner STATIC
        src/i2cscanner.c
        include/i2cscanner.h
)
add_library(Click.I2CScanner  ALIAS lib_i2cscanner)



target_include_directories(lib_i2cscanner PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cscanner PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cscanner PUBLIC MikroSDK.Driver)

