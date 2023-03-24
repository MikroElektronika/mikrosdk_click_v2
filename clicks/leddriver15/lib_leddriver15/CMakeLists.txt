cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver15 LANGUAGES MikroC)
else()
    project(lib_leddriver15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver15 STATIC
        src/leddriver15.c
        include/leddriver15.h
)
add_library(Click.LEDDriver15  ALIAS lib_leddriver15)



target_include_directories(lib_leddriver15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver15 PUBLIC MikroSDK.Driver)

