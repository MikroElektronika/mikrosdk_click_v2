cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ccrf LANGUAGES MikroC)
else()
    project(lib_ccrf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ccrf STATIC
        src/ccrf.c
        include/ccrf.h
)
add_library(Click.ccRf  ALIAS lib_ccrf)



target_include_directories(lib_ccrf PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ccrf PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ccrf PUBLIC MikroSDK.Driver)
