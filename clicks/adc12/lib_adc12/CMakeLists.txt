cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc12 LANGUAGES MikroC)
else()
    project(lib_adc12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc12 STATIC
        src/adc12.c
        include/adc12.h
)
add_library(Click.ADC12  ALIAS lib_adc12)



target_include_directories(lib_adc12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc12 PUBLIC MikroSDK.Driver)
