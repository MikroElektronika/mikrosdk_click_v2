cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac3 LANGUAGES MikroC)
else()
    project(lib_dac3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac3 STATIC
        src/dac3.c
        include/dac3.h
)
add_library(Click.DAC3  ALIAS lib_dac3)



target_include_directories(lib_dac3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac3 PUBLIC MikroSDK.Driver)
