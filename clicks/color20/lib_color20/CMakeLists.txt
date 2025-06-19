cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color20 LANGUAGES MikroC)
else()
    project(lib_color20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color20 STATIC
        src/color20.c
        include/color20.h
)
add_library(Click.Color20  ALIAS lib_color20)



target_include_directories(lib_color20 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color20 PUBLIC MikroSDK.Driver)

