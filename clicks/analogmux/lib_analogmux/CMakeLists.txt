cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_analogmux LANGUAGES MikroC)
else()
    project(lib_analogmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_analogmux STATIC
        src/analogmux.c
        include/analogmux.h
)
add_library(Click.AnalogMUX  ALIAS lib_analogmux)



target_include_directories(lib_analogmux PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_analogmux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_analogmux PUBLIC MikroSDK.Driver)
