cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc26 LANGUAGES MikroC)
else()
    project(lib_adc26 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc26 STATIC
        src/adc26.c
        include/adc26.h
)
add_library(Click.ADC26  ALIAS lib_adc26)



target_include_directories(lib_adc26 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc26 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc26 PUBLIC MikroSDK.Driver)

