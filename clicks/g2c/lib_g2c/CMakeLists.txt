cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_g2c LANGUAGES MikroC)
else()
    project(lib_g2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_g2c STATIC
        src/g2c.c
        include/g2c.h
)
add_library(Click.G2C  ALIAS lib_g2c)



target_include_directories(lib_g2c PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_g2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_g2c PUBLIC MikroSDK.Driver)
