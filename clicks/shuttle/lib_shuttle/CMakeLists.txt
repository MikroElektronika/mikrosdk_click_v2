cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_shuttle LANGUAGES MikroC)
else()
    project(lib_shuttle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_shuttle STATIC
        src/shuttle.c
        include/shuttle.h
)
add_library(Click.Shuttle  ALIAS lib_shuttle)



target_include_directories(lib_shuttle PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_shuttle PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_shuttle PUBLIC MikroSDK.Driver)
