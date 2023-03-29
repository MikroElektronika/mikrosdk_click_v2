cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_i2cmux LANGUAGES MikroC)
else()
    project(lib_i2cmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_i2cmux STATIC
        src/i2cmux.c
        include/i2cmux.h
)
add_library(Click.I2cMux  ALIAS lib_i2cmux)



target_include_directories(lib_i2cmux PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_i2cmux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_i2cmux PUBLIC MikroSDK.Driver)
