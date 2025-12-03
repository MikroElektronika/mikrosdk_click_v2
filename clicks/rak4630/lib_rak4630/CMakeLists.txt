cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rak4630 LANGUAGES MikroC)
else()
    project(lib_rak4630 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rak4630 STATIC
        src/rak4630.c
        include/rak4630.h
)
add_library(Click.RAK4630  ALIAS lib_rak4630)



target_include_directories(lib_rak4630 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rak4630 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rak4630 PUBLIC MikroSDK.Driver)

