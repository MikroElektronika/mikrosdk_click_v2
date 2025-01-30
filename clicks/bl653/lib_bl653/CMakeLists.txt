cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bl653 LANGUAGES MikroC)
else()
    project(lib_bl653 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bl653 STATIC
        src/bl653.c
        include/bl653.h
)
add_library(Click.BL653  ALIAS lib_bl653)



target_include_directories(lib_bl653 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bl653 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bl653 PUBLIC MikroSDK.Driver)

