cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_raq LANGUAGES MikroC)
else()
    project(lib_raq LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_raq STATIC
        src/raq.c
        include/raq.h
)
add_library(Click.RAQ  ALIAS lib_raq)



target_include_directories(lib_raq PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_raq PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_raq PUBLIC MikroSDK.Driver)

