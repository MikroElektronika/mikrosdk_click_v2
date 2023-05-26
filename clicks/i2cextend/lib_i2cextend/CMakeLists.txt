cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cextend LANGUAGES MikroC)
else()
    project(lib_i2cextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cextend STATIC
        src/i2cextend.c
        include/i2cextend.h
)
add_library(Click.I2CExtend  ALIAS lib_i2cextend)



target_include_directories(lib_i2cextend PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cextend PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cextend PUBLIC MikroSDK.Driver)
