cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bldcfoc LANGUAGES MikroC)
else()
    project(lib_bldcfoc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bldcfoc STATIC
        src/bldcfoc.c
        include/bldcfoc.h
)
add_library(Click.BLDCFOC  ALIAS lib_bldcfoc)



target_include_directories(lib_bldcfoc PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bldcfoc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bldcfoc PUBLIC MikroSDK.Driver)

