cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_binhonova LANGUAGES MikroC)
else()
    project(lib_binhonova LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_binhonova STATIC
        src/binhonova.c
        include/binhonova.h
)
add_library(Click.BinhoNova  ALIAS lib_binhonova)



target_include_directories(lib_binhonova PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_binhonova PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_binhonova PUBLIC MikroSDK.Driver)

