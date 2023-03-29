cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity13 LANGUAGES MikroC)
else()
    project(lib_proximity13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity13 STATIC
        src/proximity13.c
        include/proximity13.h
)
add_library(Click.Proximity13  ALIAS lib_proximity13)



target_include_directories(lib_proximity13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity13 PUBLIC MikroSDK.Driver)
