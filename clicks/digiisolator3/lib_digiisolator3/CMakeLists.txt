cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digiisolator3 LANGUAGES MikroC)
else()
    project(lib_digiisolator3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digiisolator3 STATIC
        src/digiisolator3.c
        include/digiisolator3.h
)
add_library(Click.DIGIIsolator3  ALIAS lib_digiisolator3)



target_include_directories(lib_digiisolator3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digiisolator3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digiisolator3 PUBLIC MikroSDK.Driver)

