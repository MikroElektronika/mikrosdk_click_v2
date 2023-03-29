cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uvb LANGUAGES MikroC)
else()
    project(lib_uvb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uvb STATIC
        src/uvb.c
        include/uvb.h
)
add_library(Click.UVB  ALIAS lib_uvb)



target_include_directories(lib_uvb PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uvb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uvb PUBLIC MikroSDK.Driver)
