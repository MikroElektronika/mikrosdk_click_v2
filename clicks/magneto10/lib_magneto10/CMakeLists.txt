cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto10 LANGUAGES MikroC)
else()
    project(lib_magneto10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto10 STATIC
        src/magneto10.c
        include/magneto10.h
)
add_library(Click.Magneto10  ALIAS lib_magneto10)



target_include_directories(lib_magneto10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto10 PUBLIC MikroSDK.Driver)
