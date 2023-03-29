cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c8x8g LANGUAGES MikroC)
else()
    project(lib_c8x8g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c8x8g STATIC
        src/c8x8g.c
        include/c8x8g.h
)
add_library(Click.8x8G  ALIAS lib_c8x8g)



target_include_directories(lib_c8x8g PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c8x8g PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c8x8g PUBLIC MikroSDK.Driver)
