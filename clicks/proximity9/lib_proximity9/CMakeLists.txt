cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity9 LANGUAGES MikroC)
else()
    project(lib_proximity9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity9 STATIC
        src/proximity9.c
        include/proximity9.h
)
add_library(Click.Proximity9  ALIAS lib_proximity9)



target_include_directories(lib_proximity9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity9 PUBLIC MikroSDK.Driver)
