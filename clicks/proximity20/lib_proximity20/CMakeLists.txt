cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity20 LANGUAGES MikroC)
else()
    project(lib_proximity20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity20 STATIC
        src/proximity20.c
        include/proximity20.h
)
add_library(Click.Proximity20  ALIAS lib_proximity20)



target_include_directories(lib_proximity20 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity20 PUBLIC MikroSDK.Driver)

