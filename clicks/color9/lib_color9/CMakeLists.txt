cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color9 LANGUAGES MikroC)
else()
    project(lib_color9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color9 STATIC
        src/color9.c
        include/color9.h
)
add_library(Click.Color9  ALIAS lib_color9)



target_include_directories(lib_color9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color9 PUBLIC MikroSDK.Driver)
