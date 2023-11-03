cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_press LANGUAGES MikroC)
else()
    project(lib_press LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_press STATIC
        src/press.c
        include/press.h
)
add_library(Click.PRESS  ALIAS lib_press)



target_include_directories(lib_press PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_press PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_press PUBLIC MikroSDK.Driver)

