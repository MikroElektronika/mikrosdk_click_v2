cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tdc LANGUAGES MikroC)
else()
    project(lib_tdc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tdc STATIC
        src/tdc.c
        include/tdc.h
)
add_library(Click.Tdc  ALIAS lib_tdc)



target_include_directories(lib_tdc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tdc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tdc PUBLIC MikroSDK.Driver)
