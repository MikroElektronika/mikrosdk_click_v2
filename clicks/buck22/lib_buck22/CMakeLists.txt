cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck22 LANGUAGES MikroC)
else()
    project(lib_buck22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck22 STATIC
        src/buck22.c
        include/buck22.h
)
add_library(Click.Buck22  ALIAS lib_buck22)



target_include_directories(lib_buck22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck22 PUBLIC MikroSDK.Driver)
