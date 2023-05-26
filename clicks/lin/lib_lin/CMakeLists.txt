cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lin LANGUAGES MikroC)
else()
    project(lib_lin LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lin STATIC
        src/lin.c
        include/lin.h
)
add_library(Click.Lin  ALIAS lib_lin)



target_include_directories(lib_lin PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lin PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lin PUBLIC MikroSDK.Driver)
