cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color16 LANGUAGES MikroC)
else()
    project(lib_color16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color16 STATIC
        src/color16.c
        include/color16.h
)
add_library(Click.Color16  ALIAS lib_color16)



target_include_directories(lib_color16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color16 PUBLIC MikroSDK.Driver)
