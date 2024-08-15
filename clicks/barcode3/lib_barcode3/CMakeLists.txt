cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barcode3 LANGUAGES MikroC)
else()
    project(lib_barcode3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barcode3 STATIC
        src/barcode3.c
        include/barcode3.h
)
add_library(Click.Barcode3  ALIAS lib_barcode3)



target_include_directories(lib_barcode3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barcode3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barcode3 PUBLIC MikroSDK.Driver)

