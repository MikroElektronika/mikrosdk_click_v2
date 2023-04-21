cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oledc LANGUAGES MikroC)
else()
    project(lib_oledc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oledc STATIC
        src/oledc.c
        include/oledc.h
        include/oledc_font.h
        include/oledc_image.h
)
add_library(Click.OledC  ALIAS lib_oledc)



target_include_directories(lib_oledc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oledc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oledc PUBLIC MikroSDK.Driver)
