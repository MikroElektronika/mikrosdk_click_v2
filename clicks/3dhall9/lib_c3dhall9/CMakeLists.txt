cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall9 LANGUAGES MikroC)
else()
    project(lib_c3dhall9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall9 STATIC
        src/c3dhall9.c
        include/c3dhall9.h
)
add_library(Click.3DHall9  ALIAS lib_c3dhall9)



target_include_directories(lib_c3dhall9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall9 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
