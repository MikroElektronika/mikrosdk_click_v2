cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lem LANGUAGES MikroC)
else()
    project(lib_lem LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lem STATIC
        src/lem.c
        include/lem.h
)
add_library(Click.Lem  ALIAS lib_lem)



target_include_directories(lib_lem PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lem PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lem PUBLIC MikroSDK.Driver)
