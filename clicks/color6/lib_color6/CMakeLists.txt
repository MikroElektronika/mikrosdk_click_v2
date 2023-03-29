cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color6 LANGUAGES MikroC)
else()
    project(lib_color6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color6 STATIC
        src/color6.c
        include/color6.h
)
add_library(Click.Color6  ALIAS lib_color6)



target_include_directories(lib_color6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color6 PUBLIC MikroSDK.Driver)
