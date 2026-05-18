cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3v3to5v LANGUAGES MikroC)
else()
    project(lib_c3v3to5v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3v3to5v STATIC
        src/c3v3to5v.c
        include/c3v3to5v.h
)
add_library(Click.3V3to5V  ALIAS lib_c3v3to5v)



target_include_directories(lib_c3v3to5v PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3v3to5v PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3v3to5v PUBLIC MikroSDK.Driver)

