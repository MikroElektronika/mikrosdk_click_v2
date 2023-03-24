cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_sram LANGUAGES MikroC)
else()
    project(lib_sram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_sram STATIC
        src/sram.c
        include/sram.h
)
add_library(Click.Sram  ALIAS lib_sram)



target_include_directories(lib_sram PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_sram PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_sram PUBLIC MikroSDK.Driver)
