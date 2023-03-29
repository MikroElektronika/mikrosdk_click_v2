cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge8 LANGUAGES MikroC)
else()
    project(lib_hbridge8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge8 STATIC
        src/hbridge8.c
        include/hbridge8.h
)
add_library(Click.HBridge8  ALIAS lib_hbridge8)



target_include_directories(lib_hbridge8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge8 PUBLIC MikroSDK.Driver)
