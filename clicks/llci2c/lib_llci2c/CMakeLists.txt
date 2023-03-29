cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_llci2c LANGUAGES MikroC)
else()
    project(lib_llci2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_llci2c STATIC
        src/llci2c.c
        include/llci2c.h
)
add_library(Click.LlcI2c  ALIAS lib_llci2c)



target_include_directories(lib_llci2c PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_llci2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_llci2c PUBLIC MikroSDK.Driver)
