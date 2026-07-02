cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc28 LANGUAGES MikroC)
else()
    project(lib_adc28 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc28 STATIC
        src/adc28.c
        include/adc28.h
)
add_library(Click.ADC28  ALIAS lib_adc28)



target_include_directories(lib_adc28 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc28 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc28 PUBLIC MikroSDK.Driver)

