cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c16x12 LANGUAGES MikroC)
else()
    project(lib_c16x12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c16x12 STATIC
        src/c16x12.c
        include/c16x12.h
)
add_library(Click.16x12  ALIAS lib_c16x12)



target_include_directories(lib_c16x12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c16x12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c16x12 PUBLIC MikroSDK.Driver)
