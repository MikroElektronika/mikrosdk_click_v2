cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient21 LANGUAGES MikroC)
else()
    project(lib_ambient21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient21 STATIC
        src/ambient21.c
        include/ambient21.h
)
add_library(Click.Ambient21  ALIAS lib_ambient21)



target_include_directories(lib_ambient21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient21 PUBLIC MikroSDK.Driver)

