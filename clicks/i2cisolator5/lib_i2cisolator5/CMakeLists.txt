cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cisolator5 LANGUAGES MikroC)
else()
    project(lib_i2cisolator5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cisolator5 STATIC
        src/i2cisolator5.c
        include/i2cisolator5.h
)
add_library(Click.I2CIsolator5  ALIAS lib_i2cisolator5)



target_include_directories(lib_i2cisolator5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cisolator5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cisolator5 PUBLIC MikroSDK.Driver)

