cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver18 LANGUAGES MikroC)
else()
    project(lib_leddriver18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver18 STATIC
        src/leddriver18.c
        include/leddriver18.h
)
add_library(Click.LEDDriver18  ALIAS lib_leddriver18)



target_include_directories(lib_leddriver18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver18 PUBLIC MikroSDK.Driver)

