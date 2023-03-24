cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nvsram2 LANGUAGES MikroC)
else()
    project(lib_nvsram2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nvsram2 STATIC
        src/nvsram2.c
        include/nvsram2.h
)
add_library(Click.nvSRAM2  ALIAS lib_nvsram2)



target_include_directories(lib_nvsram2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nvsram2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nvsram2 PUBLIC MikroSDK.Driver)
