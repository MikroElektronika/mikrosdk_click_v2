cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_annab412 LANGUAGES MikroC)
else()
    project(lib_annab412 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_annab412 STATIC
        src/annab412.c
        include/annab412.h
)
add_library(Click.ANNAB412  ALIAS lib_annab412)



target_include_directories(lib_annab412 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_annab412 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_annab412 PUBLIC MikroSDK.Driver)

