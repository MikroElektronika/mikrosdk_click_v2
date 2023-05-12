cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_analogmux4 LANGUAGES MikroC)
else()
    project(lib_analogmux4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_analogmux4 STATIC
        src/analogmux4.c
        include/analogmux4.h
)
add_library(Click.AnalogMUX4  ALIAS lib_analogmux4)



target_include_directories(lib_analogmux4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_analogmux4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_analogmux4 PUBLIC MikroSDK.Driver)
