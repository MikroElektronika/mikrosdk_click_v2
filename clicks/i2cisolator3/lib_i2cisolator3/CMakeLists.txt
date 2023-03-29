cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cisolator3 LANGUAGES MikroC)
else()
    project(lib_i2cisolator3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cisolator3 STATIC
        src/i2cisolator3.c
        include/i2cisolator3.h
)
add_library(Click.I2CIsolator3  ALIAS lib_i2cisolator3)



target_include_directories(lib_i2cisolator3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cisolator3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cisolator3 PUBLIC MikroSDK.Driver)
