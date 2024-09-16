cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity21 LANGUAGES MikroC)
else()
    project(lib_proximity21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity21 STATIC
        src/proximity21.c
        include/proximity21.h
)
add_library(Click.Proximity21  ALIAS lib_proximity21)



target_include_directories(lib_proximity21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity21 PUBLIC MikroSDK.Driver)

