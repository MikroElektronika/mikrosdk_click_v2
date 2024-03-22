cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_currentsens2 LANGUAGES MikroC)
else()
    project(lib_currentsens2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_currentsens2 STATIC
        src/currentsens2.c
        include/currentsens2.h
)
add_library(Click.CurrentSens2  ALIAS lib_currentsens2)



target_include_directories(lib_currentsens2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_currentsens2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_currentsens2 PUBLIC MikroSDK.Driver)

