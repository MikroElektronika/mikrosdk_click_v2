cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_adc7 LANGUAGES MikroC)
else()
    project(lib_adc7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_adc7 STATIC
        src/adc7.c
        include/adc7.h
)
add_library(Click.Adc7  ALIAS lib_adc7)



target_include_directories(lib_adc7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_adc7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_adc7 PUBLIC MikroSDK.Driver)
