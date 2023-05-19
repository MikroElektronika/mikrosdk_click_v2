cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver19 LANGUAGES MikroC)
else()
    project(lib_leddriver19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver19 STATIC
        src/leddriver19.c
        include/leddriver19.h
)
add_library(Click.LEDDriver19  ALIAS lib_leddriver19)



target_include_directories(lib_leddriver19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver19 PUBLIC MikroSDK.Driver)

