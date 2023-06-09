cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto9 LANGUAGES MikroC)
else()
    project(lib_magneto9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto9 STATIC
        src/magneto9.c
        include/magneto9.h
)
add_library(Click.Magneto9  ALIAS lib_magneto9)



target_include_directories(lib_magneto9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto9 PUBLIC MikroSDK.Driver)
