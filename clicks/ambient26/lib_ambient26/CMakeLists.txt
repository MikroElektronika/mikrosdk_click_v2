cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient26 LANGUAGES MikroC)
else()
    project(lib_ambient26 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient26 STATIC
        src/ambient26.c
        include/ambient26.h
)
add_library(Click.Ambient26  ALIAS lib_ambient26)



target_include_directories(lib_ambient26 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient26 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient26 PUBLIC MikroSDK.Driver)

