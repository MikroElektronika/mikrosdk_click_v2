cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solidswitch8 LANGUAGES MikroC)
else()
    project(lib_solidswitch8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solidswitch8 STATIC
        src/solidswitch8.c
        include/solidswitch8.h
)
add_library(Click.SolidSwitch8  ALIAS lib_solidswitch8)



target_include_directories(lib_solidswitch8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solidswitch8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solidswitch8 PUBLIC MikroSDK.Driver)

