cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless LANGUAGES MikroC)
else()
    project(lib_brushless LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless STATIC
        src/brushless.c
        include/brushless.h
)
add_library(Click.Brushless  ALIAS lib_brushless)



target_include_directories(lib_brushless PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless PUBLIC MikroSDK.Driver)
