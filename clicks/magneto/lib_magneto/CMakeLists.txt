cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto LANGUAGES MikroC)
else()
    project(lib_magneto LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto STATIC
        src/magneto.c
        include/magneto.h
)
add_library(Click.Magneto  ALIAS lib_magneto)



target_include_directories(lib_magneto PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto PUBLIC MikroSDK.Driver)
