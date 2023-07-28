cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_anynet3gea LANGUAGES MikroC)
else()
    project(lib_anynet3gea LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_anynet3gea STATIC
        src/anynet3gea.c
        include/anynet3gea.h
)
add_library(Click.AnyNet3GEA  ALIAS lib_anynet3gea)



target_include_directories(lib_anynet3gea PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_anynet3gea PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_anynet3gea PUBLIC MikroSDK.Driver)
