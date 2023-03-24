cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_waterdetect LANGUAGES MikroC)
else()
    project(lib_waterdetect LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_waterdetect STATIC
        src/waterdetect.c
        include/waterdetect.h
)
add_library(Click.WaterDetect  ALIAS lib_waterdetect)



target_include_directories(lib_waterdetect PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_waterdetect PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_waterdetect PUBLIC MikroSDK.Driver)
