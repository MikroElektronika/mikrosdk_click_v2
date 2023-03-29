cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall LANGUAGES MikroC)
else()
    project(lib_c3dhall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall STATIC
        src/c3dhall.c
        include/c3dhall.h
)
add_library(Click.3DHall  ALIAS lib_c3dhall)



target_include_directories(lib_c3dhall PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall PUBLIC MikroSDK.Driver)
