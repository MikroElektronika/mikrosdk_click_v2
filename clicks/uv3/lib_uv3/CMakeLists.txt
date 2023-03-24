cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uv3 LANGUAGES MikroC)
else()
    project(lib_uv3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uv3 STATIC
        src/uv3.c
        include/uv3.h
)
add_library(Click.Uv3  ALIAS lib_uv3)



target_include_directories(lib_uv3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uv3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uv3 PUBLIC MikroSDK.Driver)
