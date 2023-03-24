cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_angle7 LANGUAGES MikroC)
else()
    project(lib_angle7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_angle7 STATIC
        src/angle7.c
        include/angle7.h
)
add_library(Click.Angle7  ALIAS lib_angle7)



target_include_directories(lib_angle7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_angle7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_angle7 PUBLIC MikroSDK.Driver)
