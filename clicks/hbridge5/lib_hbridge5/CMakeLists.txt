cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge5 LANGUAGES MikroC)
else()
    project(lib_hbridge5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge5 STATIC
        src/hbridge5.c
        include/hbridge5.h
)
add_library(Click.HBridge5  ALIAS lib_hbridge5)



target_include_directories(lib_hbridge5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge5 PUBLIC MikroSDK.Driver)
