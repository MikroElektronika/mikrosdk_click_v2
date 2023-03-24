cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless20 LANGUAGES MikroC)
else()
    project(lib_brushless20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless20 STATIC
    src/brushless20.c
    include/brushless20.h
)
add_library(Click.Brushless20  ALIAS lib_brushless20)

target_include_directories(lib_brushless20 PUBLIC
    include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless20 PUBLIC MikroSDK.Driver)
