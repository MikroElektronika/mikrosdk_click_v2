cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp73213 LANGUAGES MikroC)
else()
    project(lib_mcp73213 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp73213 STATIC
        src/mcp73213.c
        include/mcp73213.h
)
add_library(Click.Mcp73213  ALIAS lib_mcp73213)



target_include_directories(lib_mcp73213 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp73213 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp73213 PUBLIC MikroSDK.Driver)
