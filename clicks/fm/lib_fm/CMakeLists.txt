cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fm LANGUAGES MikroC)
else()
    project(lib_fm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fm STATIC
        src/fm.c
        include/fm.h
)
add_library(Click.Fm  ALIAS lib_fm)



target_include_directories(lib_fm PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fm PUBLIC MikroSDK.Driver)
