cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fram LANGUAGES MikroC)
else()
    project(lib_fram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fram STATIC
        src/fram.c
        include/fram.h
)
add_library(Click.Fram  ALIAS lib_fram)



target_include_directories(lib_fram PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fram PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fram PUBLIC MikroSDK.Driver)
