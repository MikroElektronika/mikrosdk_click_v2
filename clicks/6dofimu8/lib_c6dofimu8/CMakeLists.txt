cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c6dofimu8 LANGUAGES MikroC)
else()
    project(lib_c6dofimu8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c6dofimu8 STATIC
        src/c6dofimu8.c
        include/c6dofimu8.h
)
add_library(Click.6DofImu8  ALIAS lib_c6dofimu8)



target_include_directories(lib_c6dofimu8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c6dofimu8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c6dofimu8 PUBLIC MikroSDK.Driver)
