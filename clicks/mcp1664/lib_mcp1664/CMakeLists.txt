cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mcp1664 LANGUAGES MikroC)
else()
    project(lib_mcp1664 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mcp1664 STATIC
        src/mcp1664.c
        include/mcp1664.h
)
add_library(Click.Mcp1664  ALIAS lib_mcp1664)



target_include_directories(lib_mcp1664 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mcp1664 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mcp1664 PUBLIC MikroSDK.Driver)
