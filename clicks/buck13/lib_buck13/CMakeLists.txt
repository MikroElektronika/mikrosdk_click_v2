cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck13 LANGUAGES MikroC)
else()
    project(lib_buck13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck13 STATIC
        src/buck13.c
        include/buck13.h
)
add_library(Click.Buck13  ALIAS lib_buck13)



target_include_directories(lib_buck13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck13 PUBLIC MikroSDK.Driver)
