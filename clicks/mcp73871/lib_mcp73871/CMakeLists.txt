cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp73871 LANGUAGES MikroC)
else()
    project(lib_mcp73871 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp73871 STATIC
        src/mcp73871.c
        include/mcp73871.h
)
add_library(Click.Mcp73871  ALIAS lib_mcp73871)



target_include_directories(lib_mcp73871 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp73871 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp73871 PUBLIC MikroSDK.Driver)
