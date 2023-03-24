cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c6dofimu2 LANGUAGES MikroC)
else()
    project(lib_c6dofimu2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c6dofimu2 STATIC
        src/c6dofimu2.c
        include/c6dofimu2.h
)
add_library(Click.6DofImu2  ALIAS lib_c6dofimu2)



target_include_directories(lib_c6dofimu2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c6dofimu2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c6dofimu2 PUBLIC MikroSDK.Driver)
