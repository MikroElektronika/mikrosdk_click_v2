cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digiisolator4 LANGUAGES MikroC)
else()
    project(lib_digiisolator4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digiisolator4 STATIC
        src/digiisolator4.c
        include/digiisolator4.h
)
add_library(Click.DIGIIsolator4  ALIAS lib_digiisolator4)



target_include_directories(lib_digiisolator4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digiisolator4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digiisolator4 PUBLIC MikroSDK.Driver)

