cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost5 LANGUAGES MikroC)
else()
    project(lib_boost5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost5 STATIC
        src/boost5.c
        include/boost5.h
)
add_library(Click.Boost5  ALIAS lib_boost5)



target_include_directories(lib_boost5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost5 PUBLIC MikroSDK.Driver)

