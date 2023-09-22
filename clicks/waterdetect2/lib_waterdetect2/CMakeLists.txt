cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_waterdetect2 LANGUAGES MikroC)
else()
    project(lib_waterdetect2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_waterdetect2 STATIC
        src/waterdetect2.c
        include/waterdetect2.h
)
add_library(Click.WaterDetect2  ALIAS lib_waterdetect2)



target_include_directories(lib_waterdetect2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_waterdetect2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_waterdetect2 PUBLIC MikroSDK.Driver)

