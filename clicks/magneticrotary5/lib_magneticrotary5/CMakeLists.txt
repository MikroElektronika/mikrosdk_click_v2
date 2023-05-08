cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneticrotary5 LANGUAGES MikroC)
else()
    project(lib_magneticrotary5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneticrotary5 STATIC
        src/magneticrotary5.c
        include/magneticrotary5.h
)
add_library(Click.MagneticRotary5  ALIAS lib_magneticrotary5)



target_include_directories(lib_magneticrotary5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneticrotary5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneticrotary5 PUBLIC MikroSDK.Driver)

