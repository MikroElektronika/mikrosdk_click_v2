cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uv4 LANGUAGES MikroC)
else()
    project(lib_uv4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uv4 STATIC
        src/uv4.c
        include/uv4.h
)
add_library(Click.UV4  ALIAS lib_uv4)



target_include_directories(lib_uv4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uv4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uv4 PUBLIC MikroSDK.Driver)
