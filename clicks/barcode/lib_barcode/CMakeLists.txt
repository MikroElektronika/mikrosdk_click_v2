cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barcode LANGUAGES MikroC)
else()
    project(lib_barcode LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barcode STATIC
        src/barcode.c
        include/barcode.h
)
add_library(Click.Barcode  ALIAS lib_barcode)



target_include_directories(lib_barcode PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barcode PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barcode PUBLIC MikroSDK.Driver)
