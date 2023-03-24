cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spiisolator LANGUAGES MikroC)
else()
    project(lib_spiisolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spiisolator STATIC
        src/spiisolator.c
        include/spiisolator.h
)
add_library(Click.Spiisolator  ALIAS lib_spiisolator)



target_include_directories(lib_spiisolator PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spiisolator PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spiisolator PUBLIC MikroSDK.Driver)
