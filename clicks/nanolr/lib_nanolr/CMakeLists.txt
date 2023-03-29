cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nanolr LANGUAGES MikroC)
else()
    project(lib_nanolr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nanolr STATIC
        src/nanolr.c
        include/nanolr.h
)
add_library(Click.NanoLR  ALIAS lib_nanolr)



target_include_directories(lib_nanolr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nanolr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nanolr PUBLIC MikroSDK.Driver)
