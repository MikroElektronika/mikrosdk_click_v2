cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c10x10rgb LANGUAGES MikroC)
else()
    project(lib_c10x10rgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c10x10rgb STATIC
        src/c10x10rgb.c
        include/c10x10rgb.h    include/c10x10rgb_ascii_matrix.h
)
add_library(Click.10x10RGB  ALIAS lib_c10x10rgb)



target_include_directories(lib_c10x10rgb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c10x10rgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c10x10rgb PUBLIC MikroSDK.Driver)
