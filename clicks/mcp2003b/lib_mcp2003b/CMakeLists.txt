cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp2003b LANGUAGES MikroC)
else()
    project(lib_mcp2003b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp2003b STATIC
        src/mcp2003b.c
        include/mcp2003b.h
)
add_library(Click.MCP2003B  ALIAS lib_mcp2003b)



target_include_directories(lib_mcp2003b PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp2003b PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp2003b PUBLIC MikroSDK.Driver)

