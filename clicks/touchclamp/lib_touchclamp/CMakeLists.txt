cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchclamp LANGUAGES MikroC)
else()
    project(lib_touchclamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchclamp STATIC
        src/touchclamp.c
        include/touchclamp.h
)
add_library(Click.TouchClamp  ALIAS lib_touchclamp)



target_include_directories(lib_touchclamp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchclamp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchclamp PUBLIC MikroSDK.Driver)
