cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost12 LANGUAGES MikroC)
else()
    project(lib_boost12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost12 STATIC
        src/boost12.c
        include/boost12.h
)
add_library(Click.Boost12  ALIAS lib_boost12)



target_include_directories(lib_boost12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost12 PUBLIC MikroSDK.Driver)

