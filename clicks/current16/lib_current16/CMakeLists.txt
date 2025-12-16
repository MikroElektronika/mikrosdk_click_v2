cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current16 LANGUAGES MikroC)
else()
    project(lib_current16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current16 STATIC
        src/current16.c
        include/current16.h
)
add_library(Click.Current16  ALIAS lib_current16)



target_include_directories(lib_current16 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current16 PUBLIC MikroSDK.Driver)

