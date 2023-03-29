cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall6 LANGUAGES MikroC)
else()
    project(lib_c3dhall6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall6 STATIC
        src/c3dhall6.c
        include/c3dhall6.h
)
add_library(Click.3dHall6  ALIAS lib_c3dhall6)



target_include_directories(lib_c3dhall6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall6 PUBLIC MikroSDK.Driver)
