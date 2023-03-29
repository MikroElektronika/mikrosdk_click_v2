cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc9 LANGUAGES MikroC)
else()
    project(lib_adc9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc9 STATIC
        src/adc9.c
        include/adc9.h
)
add_library(Click.Adc9  ALIAS lib_adc9)



target_include_directories(lib_adc9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc9 PUBLIC MikroSDK.Driver)
