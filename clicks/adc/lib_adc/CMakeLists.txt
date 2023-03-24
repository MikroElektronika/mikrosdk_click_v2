cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc LANGUAGES MikroC)
else()
    project(lib_adc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc STATIC
        src/adc.c
        include/adc.h
)
add_library(Click.Adc  ALIAS lib_adc)



target_include_directories(lib_adc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc PUBLIC MikroSDK.Driver)
