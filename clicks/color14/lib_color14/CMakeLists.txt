cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color14 LANGUAGES MikroC)
else()
    project(lib_color14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color14 STATIC
        src/color14.c
        include/color14.h
)
add_library(Click.Color14  ALIAS lib_color14)



target_include_directories(lib_color14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color14 PUBLIC MikroSDK.Driver)
