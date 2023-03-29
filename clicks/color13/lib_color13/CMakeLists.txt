cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color13 LANGUAGES MikroC)
else()
    project(lib_color13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color13 STATIC
        src/color13.c
        include/color13.h
)
add_library(Click.Color13  ALIAS lib_color13)



target_include_directories(lib_color13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color13 PUBLIC MikroSDK.Driver)
