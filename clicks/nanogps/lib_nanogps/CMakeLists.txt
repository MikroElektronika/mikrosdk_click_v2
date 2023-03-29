cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nanogps LANGUAGES MikroC)
else()
    project(lib_nanogps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nanogps STATIC
        src/nanogps.c
        include/nanogps.h
)
add_library(Click.Nanogps  ALIAS lib_nanogps)



target_include_directories(lib_nanogps PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nanogps PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nanogps PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_nanogps PUBLIC MikroSDK.GenericPointer)
