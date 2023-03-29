cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pixi LANGUAGES MikroC)
else()
    project(lib_pixi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pixi STATIC
        src/pixi.c
        include/pixi.h
)
add_library(Click.Pixi  ALIAS lib_pixi)



target_include_directories(lib_pixi PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pixi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pixi PUBLIC MikroSDK.Driver)
