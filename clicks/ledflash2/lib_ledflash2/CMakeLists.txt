cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledflash2 LANGUAGES MikroC)
else()
    project(lib_ledflash2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledflash2 STATIC
        src/ledflash2.c
        include/ledflash2.h
)
add_library(Click.LedFlash2  ALIAS lib_ledflash2)



target_include_directories(lib_ledflash2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledflash2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledflash2 PUBLIC MikroSDK.Driver)
