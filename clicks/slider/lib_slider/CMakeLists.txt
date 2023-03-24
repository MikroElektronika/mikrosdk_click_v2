cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_slider LANGUAGES MikroC)
else()
    project(lib_slider LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_slider STATIC
        src/slider.c
        include/slider.h
)
add_library(Click.Slider  ALIAS lib_slider)



target_include_directories(lib_slider PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_slider PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_slider PUBLIC MikroSDK.Driver)
