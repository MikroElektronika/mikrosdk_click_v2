cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash2 LANGUAGES MikroC)
else()
    project(lib_flash2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash2 STATIC
        src/flash2.c
        include/flash2.h
)
add_library(Click.Flash2  ALIAS lib_flash2)



target_include_directories(lib_flash2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash2 PUBLIC MikroSDK.Driver)
