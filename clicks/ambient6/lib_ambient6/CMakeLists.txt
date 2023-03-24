cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient6 LANGUAGES MikroC)
else()
    project(lib_ambient6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient6 STATIC
        src/ambient6.c
        include/ambient6.h
)
add_library(Click.Ambient6  ALIAS lib_ambient6)



target_include_directories(lib_ambient6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient6 PUBLIC MikroSDK.Driver)
