cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_leddriver17 LANGUAGES MikroC)
else()
    project(lib_leddriver17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_leddriver17 STATIC
        src/leddriver17.c
        include/leddriver17.h
)
add_library(Click.LEDDriver17  ALIAS lib_leddriver17)



target_include_directories(lib_leddriver17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_leddriver17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_leddriver17 PUBLIC MikroSDK.Driver)

