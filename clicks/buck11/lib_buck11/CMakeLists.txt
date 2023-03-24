cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck11 LANGUAGES MikroC)
else()
    project(lib_buck11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck11 STATIC
        src/buck11.c
        include/buck11.h
)
add_library(Click.Buck11  ALIAS lib_buck11)



target_include_directories(lib_buck11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck11 PUBLIC MikroSDK.Driver)
