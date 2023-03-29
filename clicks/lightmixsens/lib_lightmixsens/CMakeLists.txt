cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lightmixsens LANGUAGES MikroC)
else()
    project(lib_lightmixsens LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lightmixsens STATIC
        src/lightmixsens.c
        include/lightmixsens.h
)
add_library(Click.LightMixSens  ALIAS lib_lightmixsens)



target_include_directories(lib_lightmixsens PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lightmixsens PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lightmixsens PUBLIC MikroSDK.Driver)
