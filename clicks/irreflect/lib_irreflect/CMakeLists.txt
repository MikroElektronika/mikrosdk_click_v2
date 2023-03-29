cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irreflect LANGUAGES MikroC)
else()
    project(lib_irreflect LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irreflect STATIC
        src/irreflect.c
        include/irreflect.h
)
add_library(Click.IrReflect  ALIAS lib_irreflect)



target_include_directories(lib_irreflect PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irreflect PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irreflect PUBLIC MikroSDK.Driver)
