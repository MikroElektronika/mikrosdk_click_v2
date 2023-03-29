cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck12 LANGUAGES MikroC)
else()
    project(lib_buck12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck12 STATIC
        src/buck12.c
        include/buck12.h
)
add_library(Click.Buck12  ALIAS lib_buck12)



target_include_directories(lib_buck12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck12 PUBLIC MikroSDK.Driver)
