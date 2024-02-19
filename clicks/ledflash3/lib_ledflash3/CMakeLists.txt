cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledflash3 LANGUAGES MikroC)
else()
    project(lib_ledflash3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledflash3 STATIC
        src/ledflash3.c
        include/ledflash3.h
)
add_library(Click.LEDFlash3  ALIAS lib_ledflash3)



target_include_directories(lib_ledflash3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledflash3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledflash3 PUBLIC MikroSDK.Driver)

