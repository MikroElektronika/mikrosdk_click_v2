cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4gltena LANGUAGES MikroC)
else()
    project(lib_c4gltena LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4gltena STATIC
        src/c4gltena.c
        include/c4gltena.h
)
add_library(Click.4GLTENA  ALIAS lib_c4gltena)



target_include_directories(lib_c4gltena PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4gltena PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4gltena PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4gltena PUBLIC MikroSDK.Conversions)
