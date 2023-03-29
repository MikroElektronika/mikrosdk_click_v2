cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ldc1101 LANGUAGES MikroC)
else()
    project(lib_ldc1101 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ldc1101 STATIC
        src/ldc1101.c
        include/ldc1101.h
)
add_library(Click.Ldc1101  ALIAS lib_ldc1101)



target_include_directories(lib_ldc1101 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ldc1101 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ldc1101 PUBLIC MikroSDK.Driver)
