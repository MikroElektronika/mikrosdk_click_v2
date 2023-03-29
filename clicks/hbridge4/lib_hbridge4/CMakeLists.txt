cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge4 LANGUAGES MikroC)
else()
    project(lib_hbridge4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge4 STATIC
        src/hbridge4.c
        include/hbridge4.h
)
add_library(Click.HBridge4  ALIAS lib_hbridge4)



target_include_directories(lib_hbridge4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge4 PUBLIC MikroSDK.Driver)
