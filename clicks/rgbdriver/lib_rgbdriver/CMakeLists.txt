cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rgbdriver LANGUAGES MikroC)
else()
    project(lib_rgbdriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rgbdriver STATIC
        src/rgbdriver.c
        include/rgbdriver.h
)
add_library(Click.RgbDriver  ALIAS lib_rgbdriver)



target_include_directories(lib_rgbdriver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rgbdriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rgbdriver PUBLIC MikroSDK.Driver)
