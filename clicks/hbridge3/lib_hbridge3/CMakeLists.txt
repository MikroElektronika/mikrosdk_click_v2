cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge3 LANGUAGES MikroC)
else()
    project(lib_hbridge3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge3 STATIC
        src/hbridge3.c
        include/hbridge3.h
)
add_library(Click.HBridge3  ALIAS lib_hbridge3)



target_include_directories(lib_hbridge3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge3 PUBLIC MikroSDK.Driver)
