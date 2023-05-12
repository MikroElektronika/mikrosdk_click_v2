cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp2542 LANGUAGES MikroC)
else()
    project(lib_mcp2542 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp2542 STATIC
        src/mcp2542.c
        include/mcp2542.h
)
add_library(Click.Mcp2542  ALIAS lib_mcp2542)



target_include_directories(lib_mcp2542 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp2542 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp2542 PUBLIC MikroSDK.Driver)
