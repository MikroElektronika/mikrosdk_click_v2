cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_noise LANGUAGES MikroC)
else()
    project(lib_noise LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_noise STATIC
        src/noise.c
        include/noise.h
)
add_library(Click.Noise  ALIAS lib_noise)



target_include_directories(lib_noise PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_noise PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_noise PUBLIC MikroSDK.Driver)
