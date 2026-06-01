cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_opto8 LANGUAGES MikroC)
else()
    project(lib_opto8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_opto8 STATIC
        src/opto8.c
        include/opto8.h
)
add_library(Click.Opto8  ALIAS lib_opto8)



target_include_directories(lib_opto8 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_opto8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_opto8 PUBLIC MikroSDK.Driver)

