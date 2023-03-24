cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat1eu LANGUAGES MikroC)
else()
    project(lib_ltecat1eu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat1eu STATIC
        src/ltecat1eu.c
        include/ltecat1eu.h
)
add_library(Click.LTECat1EU  ALIAS lib_ltecat1eu)



target_include_directories(lib_ltecat1eu PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat1eu PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat1eu PUBLIC MikroSDK.Driver)
