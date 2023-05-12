cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_analogmux5 LANGUAGES MikroC)
else()
    project(lib_analogmux5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_analogmux5 STATIC
        src/analogmux5.c
        include/analogmux5.h
)
add_library(Click.AnalogMUX5  ALIAS lib_analogmux5)



target_include_directories(lib_analogmux5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_analogmux5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_analogmux5 PUBLIC MikroSDK.Driver)
