cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thyonei LANGUAGES MikroC)
else()
    project(lib_thyonei LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thyonei STATIC
        src/thyonei.c
        include/thyonei.h
)
add_library(Click.ThyoneI  ALIAS lib_thyonei)



target_include_directories(lib_thyonei PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thyonei PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thyonei PUBLIC MikroSDK.Driver)

