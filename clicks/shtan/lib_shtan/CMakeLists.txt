cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_shtan LANGUAGES MikroC)
else()
    project(lib_shtan LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_shtan STATIC
        src/shtan.c
        include/shtan.h
)
add_library(Click.ShtAn  ALIAS lib_shtan)



target_include_directories(lib_shtan PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_shtan PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_shtan PUBLIC MikroSDK.Driver)
