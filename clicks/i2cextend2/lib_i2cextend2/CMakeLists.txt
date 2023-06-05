cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cextend2 LANGUAGES MikroC)
else()
    project(lib_i2cextend2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cextend2 STATIC
        src/i2cextend2.c
        include/i2cextend2.h
)
add_library(Click.I2CExtend2  ALIAS lib_i2cextend2)



target_include_directories(lib_i2cextend2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cextend2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cextend2 PUBLIC MikroSDK.Driver)
