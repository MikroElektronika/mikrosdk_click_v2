cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto8 LANGUAGES MikroC)
else()
    project(lib_magneto8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto8 STATIC
        src/magneto8.c
        include/magneto8.h
)
add_library(Click.Magneto8  ALIAS lib_magneto8)



target_include_directories(lib_magneto8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto8 PUBLIC MikroSDK.Driver)
