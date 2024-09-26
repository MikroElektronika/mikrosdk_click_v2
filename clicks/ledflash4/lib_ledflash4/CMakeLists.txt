cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledflash4 LANGUAGES MikroC)
else()
    project(lib_ledflash4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledflash4 STATIC
        src/ledflash4.c
        include/ledflash4.h
)
add_library(Click.LEDFlash4  ALIAS lib_ledflash4)



target_include_directories(lib_ledflash4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledflash4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledflash4 PUBLIC MikroSDK.Driver)

