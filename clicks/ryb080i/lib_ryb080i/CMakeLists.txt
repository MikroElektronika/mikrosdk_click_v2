cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ryb080i LANGUAGES MikroC)
else()
    project(lib_ryb080i LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ryb080i STATIC
        src/ryb080i.c
        include/ryb080i.h
)
add_library(Click.RYB080I  ALIAS lib_ryb080i)



target_include_directories(lib_ryb080i PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ryb080i PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ryb080i PUBLIC MikroSDK.Driver)

