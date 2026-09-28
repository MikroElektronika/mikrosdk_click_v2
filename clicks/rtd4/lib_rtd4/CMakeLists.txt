cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtd4 LANGUAGES MikroC)
else()
    project(lib_rtd4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtd4 STATIC
        src/rtd4.c
        include/rtd4.h
)
add_library(Click.RTD4  ALIAS lib_rtd4)



target_include_directories(lib_rtd4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtd4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtd4 PUBLIC MikroSDK.Driver)

