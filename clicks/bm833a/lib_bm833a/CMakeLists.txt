cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bm833a LANGUAGES MikroC)
else()
    project(lib_bm833a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bm833a STATIC
        src/bm833a.c
        include/bm833a.h
)
add_library(Click.BM833A  ALIAS lib_bm833a)



target_include_directories(lib_bm833a PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bm833a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bm833a PUBLIC MikroSDK.Driver)

