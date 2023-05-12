cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nplc LANGUAGES MikroC)
else()
    project(lib_nplc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nplc STATIC
        src/nplc.c
        include/nplc.h
)
add_library(Click.NPLC  ALIAS lib_nplc)



target_include_directories(lib_nplc PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nplc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nplc PUBLIC MikroSDK.Driver)

