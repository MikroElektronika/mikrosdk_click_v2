cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c1wirei2c LANGUAGES MikroC)
else()
    project(lib_c1wirei2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c1wirei2c STATIC
        src/c1wirei2c.c
        include/c1wirei2c.h
)
add_library(Click.1WireI2C  ALIAS lib_c1wirei2c)



target_include_directories(lib_c1wirei2c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c1wirei2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c1wirei2c PUBLIC MikroSDK.Driver)

