cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color12 LANGUAGES MikroC)
else()
    project(lib_color12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color12 STATIC
        src/color12.c
        include/color12.h
)
add_library(Click.Color12  ALIAS lib_color12)



target_include_directories(lib_color12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color12 PUBLIC MikroSDK.Driver)

