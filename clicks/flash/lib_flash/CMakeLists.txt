cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash LANGUAGES MikroC)
else()
    project(lib_flash LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash STATIC
        src/flash.c
        include/flash.h
)
add_library(Click.Flash  ALIAS lib_flash)



target_include_directories(lib_flash PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash PUBLIC MikroSDK.Driver)
