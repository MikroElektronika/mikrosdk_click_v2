cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs232toi2c LANGUAGES MikroC)
else()
    project(lib_rs232toi2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs232toi2c STATIC
        src/rs232toi2c.c
        include/rs232toi2c.h
)
add_library(Click.RS232toI2C  ALIAS lib_rs232toi2c)



target_include_directories(lib_rs232toi2c PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs232toi2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs232toi2c PUBLIC MikroSDK.Driver)
