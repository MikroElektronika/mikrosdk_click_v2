cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4ddisplay LANGUAGES MikroC)
else()
    project(lib_c4ddisplay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4ddisplay STATIC
        src/c4ddisplay.c
        include/c4ddisplay.h
)
add_library(Click.4Ddisplay  ALIAS lib_c4ddisplay)



target_include_directories(lib_c4ddisplay PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4ddisplay PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4ddisplay PUBLIC MikroSDK.Driver)

