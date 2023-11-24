cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless13 LANGUAGES MikroC)
else()
    project(lib_brushless13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless13 STATIC
        src/brushless13.c
        include/brushless13.h
)
add_library(Click.Brushless13  ALIAS lib_brushless13)



target_include_directories(lib_brushless13 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless13 PUBLIC MikroSDK.Driver)

