cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand13 LANGUAGES MikroC)
else()
    project(lib_expand13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand13 STATIC
        src/expand13.c
        include/expand13.h
)
add_library(Click.Expand13  ALIAS lib_expand13)



target_include_directories(lib_expand13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand13 PUBLIC MikroSDK.Driver)
