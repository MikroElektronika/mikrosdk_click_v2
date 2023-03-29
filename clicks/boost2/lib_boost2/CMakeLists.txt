cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost2 LANGUAGES MikroC)
else()
    project(lib_boost2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost2 STATIC
        src/boost2.c
        include/boost2.h
)
add_library(Click.Boost2  ALIAS lib_boost2)



target_include_directories(lib_boost2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost2 PUBLIC MikroSDK.Driver)
