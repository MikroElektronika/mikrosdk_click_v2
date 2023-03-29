cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4dotmatrixr LANGUAGES MikroC)
else()
    project(lib_c4dotmatrixr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4dotmatrixr STATIC
        src/c4dotmatrixr.c
        include/c4dotmatrixr.h
)
add_library(Click.4dotmatrixr  ALIAS lib_c4dotmatrixr)



target_include_directories(lib_c4dotmatrixr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4dotmatrixr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4dotmatrixr PUBLIC MikroSDK.Driver)
