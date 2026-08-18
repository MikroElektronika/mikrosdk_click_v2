cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall17 LANGUAGES MikroC)
else()
    project(lib_c3dhall17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall17 STATIC
        src/c3dhall17.c
        include/c3dhall17.h
)
add_library(Click.3DHall17  ALIAS lib_c3dhall17)



target_include_directories(lib_c3dhall17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall17 PUBLIC MikroSDK.Driver)

