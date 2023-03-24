cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_environment  LANGUAGES MikroC)
else()
    project(lib_environment  LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_environment  STATIC
        src/environment.c
        include/environment.h
)
add_library(Click.Environment  ALIAS lib_environment )



target_include_directories(lib_environment  PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_environment  PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_environment  PUBLIC MikroSDK.Driver)
