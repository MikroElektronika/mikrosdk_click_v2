cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_optoencoder6 LANGUAGES MikroC)
else()
    project(lib_optoencoder6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_optoencoder6 STATIC
        src/optoencoder6.c
        include/optoencoder6.h
)
add_library(Click.OptoEncoder6  ALIAS lib_optoencoder6)



target_include_directories(lib_optoencoder6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_optoencoder6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_optoencoder6 PUBLIC MikroSDK.Driver)

