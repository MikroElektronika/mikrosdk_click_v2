cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_big7seg LANGUAGES MikroC)
else()
    project(lib_big7seg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_big7seg STATIC
        src/big7seg.c
        include/big7seg.h
)
add_library(Click.Big7Seg  ALIAS lib_big7seg)



target_include_directories(lib_big7seg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_big7seg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_big7seg PUBLIC MikroSDK.Driver)
