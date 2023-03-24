cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_angle LANGUAGES MikroC)
else()
    project(lib_angle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_angle STATIC
        src/angle.c
        include/angle.h
)
add_library(Click.Angle  ALIAS lib_angle)



target_include_directories(lib_angle PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_angle PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_angle PUBLIC MikroSDK.Driver)
