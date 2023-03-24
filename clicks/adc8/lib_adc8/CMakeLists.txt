cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc8 LANGUAGES MikroC)
else()
    project(lib_adc8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc8 STATIC
        src/adc8.c
        include/adc8.h
)
add_library(Click.Adc8  ALIAS lib_adc8)



target_include_directories(lib_adc8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc8 PUBLIC MikroSDK.Driver)
