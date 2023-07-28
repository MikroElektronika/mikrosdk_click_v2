cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_anynet3gaa LANGUAGES MikroC)
else()
    project(lib_anynet3gaa LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_anynet3gaa STATIC
        src/anynet3gaa.c
        include/anynet3gaa.h
)
add_library(Click.AnyNet3GAA  ALIAS lib_anynet3gaa)



target_include_directories(lib_anynet3gaa PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_anynet3gaa PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_anynet3gaa PUBLIC MikroSDK.Driver)
