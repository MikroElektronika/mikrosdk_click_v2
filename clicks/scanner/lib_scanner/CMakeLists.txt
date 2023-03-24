cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_scanner LANGUAGES MikroC)
else()
    project(lib_scanner LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_scanner STATIC
        src/scanner.c
        include/scanner.h
)
add_library(Click.Scanner  ALIAS lib_scanner)



target_include_directories(lib_scanner PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_scanner PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_scanner PUBLIC MikroSDK.Driver)
