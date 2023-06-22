cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uv LANGUAGES MikroC)
else()
    project(lib_uv LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uv STATIC
        src/uv.c
        include/uv.h
)
add_library(Click.Uv  ALIAS lib_uv)



target_include_directories(lib_uv PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uv PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uv PUBLIC MikroSDK.Driver)
