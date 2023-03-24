cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gps LANGUAGES MikroC)
else()
    project(lib_gps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gps STATIC
        src/gps.c
        include/gps.h
)
add_library(Click.Gps  ALIAS lib_gps)



target_include_directories(lib_gps PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gps PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gps PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gps PUBLIC MikroSDK.GenericPointer)
