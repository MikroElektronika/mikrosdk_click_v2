cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_sram2 LANGUAGES MikroC)
else()
    project(lib_sram2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_sram2 STATIC
        src/sram2.c
        include/sram2.h
)
add_library(Click.Sram2  ALIAS lib_sram2)



target_include_directories(lib_sram2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_sram2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_sram2 PUBLIC MikroSDK.Driver)
