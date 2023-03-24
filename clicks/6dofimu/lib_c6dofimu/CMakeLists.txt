cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c6dofimu LANGUAGES MikroC)
else()
    project(lib_c6dofimu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c6dofimu STATIC
        src/c6dofimu.c
        include/c6dofimu.h
)
add_library(Click.6DofImu  ALIAS lib_c6dofimu)



target_include_directories(lib_c6dofimu PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c6dofimu PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c6dofimu PUBLIC MikroSDK.Driver)
