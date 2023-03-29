cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto11 LANGUAGES MikroC)
else()
    project(lib_magneto11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto11 STATIC
        src/magneto11.c
        include/magneto11.h
)
add_library(Click.Magneto11  ALIAS lib_magneto11)



target_include_directories(lib_magneto11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto11 PUBLIC MikroSDK.Driver)
