cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp16331 LANGUAGES MikroC)
else()
    project(lib_mcp16331 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp16331 STATIC
        src/mcp16331.c
        include/mcp16331.h
)
add_library(Click.Mcp16331  ALIAS lib_mcp16331)



target_include_directories(lib_mcp16331 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp16331 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp16331 PUBLIC MikroSDK.Driver)
