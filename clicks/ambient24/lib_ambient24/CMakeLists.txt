cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient24 LANGUAGES MikroC)
else()
    project(lib_ambient24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient24 STATIC
        src/ambient24.c
        include/ambient24.h
)
add_library(Click.Ambient24  ALIAS lib_ambient24)



target_include_directories(lib_ambient24 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient24 PUBLIC MikroSDK.Driver)

