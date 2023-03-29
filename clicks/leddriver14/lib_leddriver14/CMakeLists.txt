cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver14 LANGUAGES MikroC)
else()
    project(lib_leddriver14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver14 STATIC
        src/leddriver14.c
        include/leddriver14.h
)
add_library(Click.LEDDriver14  ALIAS lib_leddriver14)



target_include_directories(lib_leddriver14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver14 PUBLIC MikroSDK.Driver)
