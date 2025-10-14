cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2crepeater LANGUAGES MikroC)
else()
    project(lib_i2crepeater LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2crepeater STATIC
        src/i2crepeater.c
        include/i2crepeater.h
)
add_library(Click.I2CRepeater  ALIAS lib_i2crepeater)



target_include_directories(lib_i2crepeater PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2crepeater PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2crepeater PUBLIC MikroSDK.Driver)

