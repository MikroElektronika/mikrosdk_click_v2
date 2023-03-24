cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc2 LANGUAGES MikroC)
else()
    project(lib_adc2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc2 STATIC
        src/adc2.c
        include/adc2.h
)
add_library(Click.Adc2  ALIAS lib_adc2)



target_include_directories(lib_adc2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc2 PUBLIC MikroSDK.Driver)
