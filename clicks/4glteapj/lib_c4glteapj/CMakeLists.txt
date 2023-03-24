cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glteapj LANGUAGES MikroC)
else()
    project(lib_c4glteapj LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glteapj STATIC
        src/c4glteapj.c
        include/c4glteapj.h
)
add_library(Click.4GLTEAPJ  ALIAS lib_c4glteapj)



target_include_directories(lib_c4glteapj PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glteapj PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glteapj PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glteapj PUBLIC MikroSDK.Conversions)
