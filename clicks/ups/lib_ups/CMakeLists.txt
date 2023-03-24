cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ups LANGUAGES MikroC)
else()
    project(lib_ups LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ups STATIC
        src/ups.c
        include/ups.h
)
add_library(Click.Ups  ALIAS lib_ups)



target_include_directories(lib_ups PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ups PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ups PUBLIC MikroSDK.Driver)
