cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gsr LANGUAGES MikroC)
else()
    project(lib_gsr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gsr STATIC
        src/gsr.c
        include/gsr.h
)
add_library(Click.Gsr  ALIAS lib_gsr)



target_include_directories(lib_gsr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gsr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gsr PUBLIC MikroSDK.Driver)
