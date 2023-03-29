cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color LANGUAGES MikroC)
else()
    project(lib_color LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color STATIC
        src/color.c
        include/color.h
)
add_library(Click.Color  ALIAS lib_color)



target_include_directories(lib_color PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color PUBLIC MikroSDK.Driver)
