cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_obdii LANGUAGES MikroC)
else()
    project(lib_obdii LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_obdii STATIC
        src/obdii.c
        include/obdii.h
)
add_library(Click.OBDII  ALIAS lib_obdii)



target_include_directories(lib_obdii PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_obdii PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_obdii PUBLIC MikroSDK.Driver)

