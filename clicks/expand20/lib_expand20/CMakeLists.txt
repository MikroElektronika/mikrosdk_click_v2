cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand20 LANGUAGES MikroC)
else()
    project(lib_expand20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand20 STATIC
        src/expand20.c
        include/expand20.h
)
add_library(Click.Expand20  ALIAS lib_expand20)



target_include_directories(lib_expand20 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand20 PUBLIC MikroSDK.Driver)

