cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ccrf2 LANGUAGES MikroC)
else()
    project(lib_ccrf2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ccrf2 STATIC
        src/ccrf2.c
        include/ccrf2.h
)
add_library(Click.ccRf2  ALIAS lib_ccrf2)



target_include_directories(lib_ccrf2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ccrf2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ccrf2 PUBLIC MikroSDK.Driver)
