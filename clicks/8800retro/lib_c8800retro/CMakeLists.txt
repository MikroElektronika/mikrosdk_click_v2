cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c8800retro LANGUAGES MikroC)
else()
    project(lib_c8800retro LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c8800retro STATIC
        src/c8800retro.c
        include/c8800retro.h
)
add_library(Click.8800Retro  ALIAS lib_c8800retro)



target_include_directories(lib_c8800retro PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c8800retro PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c8800retro PUBLIC MikroSDK.Driver)
