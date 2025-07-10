cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xportedge LANGUAGES MikroC)
else()
    project(lib_xportedge LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xportedge STATIC
        src/xportedge.c
        include/xportedge.h
)
add_library(Click.XPortEDGE  ALIAS lib_xportedge)



target_include_directories(lib_xportedge PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xportedge PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xportedge PUBLIC MikroSDK.Driver)

