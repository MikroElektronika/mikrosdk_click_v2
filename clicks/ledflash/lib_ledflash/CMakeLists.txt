cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledflash LANGUAGES MikroC)
else()
    project(lib_ledflash LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledflash STATIC
        src/ledflash.c
        include/ledflash.h
)
add_library(Click.LedFlash  ALIAS lib_ledflash)



target_include_directories(lib_ledflash PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledflash PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledflash PUBLIC MikroSDK.Driver)
