cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneticrotary LANGUAGES MikroC)
else()
    project(lib_magneticrotary LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneticrotary STATIC
        src/magneticrotary.c
        include/magneticrotary.h
)
add_library(Click.MagneticRotary  ALIAS lib_magneticrotary)



target_include_directories(lib_magneticrotary PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneticrotary PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneticrotary PUBLIC MikroSDK.Driver)
