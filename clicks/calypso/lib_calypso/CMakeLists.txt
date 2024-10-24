cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_calypso LANGUAGES MikroC)
else()
    project(lib_calypso LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_calypso STATIC
        src/calypso.c
        include/calypso.h
)
add_library(Click.Calypso  ALIAS lib_calypso)



target_include_directories(lib_calypso PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_calypso PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_calypso PUBLIC MikroSDK.Driver)

