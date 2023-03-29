cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_analogmux2 LANGUAGES MikroC)
else()
    project(lib_analogmux2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_analogmux2 STATIC
        src/analogmux2.c
        include/analogmux2.h
)
add_library(Click.AnalogMux2  ALIAS lib_analogmux2)



target_include_directories(lib_analogmux2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_analogmux2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_analogmux2 PUBLIC MikroSDK.Driver)
