cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hydrogen LANGUAGES MikroC)
else()
    project(lib_hydrogen LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hydrogen STATIC
        src/hydrogen.c
        include/hydrogen.h
)
add_library(Click.Hydrogen  ALIAS lib_hydrogen)



target_include_directories(lib_hydrogen PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hydrogen PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hydrogen PUBLIC MikroSDK.Driver)
