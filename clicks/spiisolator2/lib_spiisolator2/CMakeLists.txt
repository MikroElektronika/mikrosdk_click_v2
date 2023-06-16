cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spiisolator2 LANGUAGES MikroC)
else()
    project(lib_spiisolator2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spiisolator2 STATIC
        src/spiisolator2.c
        include/spiisolator2.h
)
add_library(Click.SPIIsolator2  ALIAS lib_spiisolator2)



target_include_directories(lib_spiisolator2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spiisolator2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spiisolator2 PUBLIC MikroSDK.Driver)
