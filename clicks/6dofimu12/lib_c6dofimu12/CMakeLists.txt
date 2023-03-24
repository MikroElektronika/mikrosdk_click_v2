cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c6dofimu12 LANGUAGES MikroC)
else()
    project(lib_c6dofimu12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c6dofimu12 STATIC
        src/c6dofimu12.c
        include/c6dofimu12.h    include/c6dofimu12_config.h
)
add_library(Click.6DofImu12  ALIAS lib_c6dofimu12)



target_include_directories(lib_c6dofimu12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c6dofimu12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c6dofimu12 PUBLIC MikroSDK.Driver)
