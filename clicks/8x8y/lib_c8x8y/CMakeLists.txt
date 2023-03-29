cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c8x8y LANGUAGES MikroC)
else()
    project(lib_c8x8y LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c8x8y STATIC
        src/c8x8y.c
        include/c8x8y.h
)
add_library(Click.8x8Y  ALIAS lib_c8x8y)



target_include_directories(lib_c8x8y PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c8x8y PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c8x8y PUBLIC MikroSDK.Driver)
