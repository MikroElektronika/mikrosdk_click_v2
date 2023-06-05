cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pollution LANGUAGES MikroC)
else()
    project(lib_pollution LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pollution STATIC
        src/pollution.c
        include/pollution.h
)
add_library(Click.Pollution  ALIAS lib_pollution)



target_include_directories(lib_pollution PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pollution PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pollution PUBLIC MikroSDK.Driver)
