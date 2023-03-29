cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck LANGUAGES MikroC)
else()
    project(lib_buck LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck STATIC
        src/buck.c
        include/buck.h
)
add_library(Click.Buck  ALIAS lib_buck)



target_include_directories(lib_buck PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck PUBLIC MikroSDK.Driver)
