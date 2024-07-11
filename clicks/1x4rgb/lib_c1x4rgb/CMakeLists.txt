cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c1x4rgb LANGUAGES MikroC)
else()
    project(lib_c1x4rgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c1x4rgb STATIC
        src/c1x4rgb.c
        include/c1x4rgb.h
)
add_library(Click.1x4RGB  ALIAS lib_c1x4rgb)



target_include_directories(lib_c1x4rgb PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c1x4rgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c1x4rgb PUBLIC MikroSDK.Driver)

