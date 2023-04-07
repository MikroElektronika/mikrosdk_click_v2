cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ledring2 LANGUAGES MikroC)
else()
    project(lib_ledring2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ledring2 STATIC
        src/ledring2.c
        include/ledring2.h
)
add_library(Click.LEDRing2  ALIAS lib_ledring2)



target_include_directories(lib_ledring2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ledring2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ledring2 PUBLIC MikroSDK.Driver)

