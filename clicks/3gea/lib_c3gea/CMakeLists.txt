cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3gea LANGUAGES MikroC)
else()
    project(lib_c3gea LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3gea STATIC
        src/c3gea.c
        include/c3gea.h
)
add_library(Click.3GEA  ALIAS lib_c3gea)



target_include_directories(lib_c3gea PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3gea PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3gea PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c3gea PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c3gea PUBLIC MikroSDK.GenericPointer)
