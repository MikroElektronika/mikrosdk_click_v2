cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash8 LANGUAGES MikroC)
else()
    project(lib_flash8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash8 STATIC
        src/flash8.c
        include/flash8.h
)
add_library(Click.Flash8  ALIAS lib_flash8)



target_include_directories(lib_flash8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash8 PUBLIC MikroSDK.Driver)
