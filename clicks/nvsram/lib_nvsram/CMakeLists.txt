cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nvsram LANGUAGES MikroC)
else()
    project(lib_nvsram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nvsram STATIC
        src/nvsram.c
        include/nvsram.h
)
add_library(Click.nvSRAM  ALIAS lib_nvsram)



target_include_directories(lib_nvsram PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nvsram PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nvsram PUBLIC MikroSDK.Driver)
