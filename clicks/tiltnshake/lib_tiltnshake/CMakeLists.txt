cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tiltnshake LANGUAGES MikroC)
else()
    project(lib_tiltnshake LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tiltnshake STATIC
        src/tiltnshake.c
        include/tiltnshake.h
)
add_library(Click.TiltNshake  ALIAS lib_tiltnshake)



target_include_directories(lib_tiltnshake PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tiltnshake PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tiltnshake PUBLIC MikroSDK.Driver)
