cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vacuum2 LANGUAGES MikroC)
else()
    project(lib_vacuum2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vacuum2 STATIC
        src/vacuum2.c
        include/vacuum2.h
)
add_library(Click.Vacuum2  ALIAS lib_vacuum2)



target_include_directories(lib_vacuum2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vacuum2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vacuum2 PUBLIC MikroSDK.Driver)

