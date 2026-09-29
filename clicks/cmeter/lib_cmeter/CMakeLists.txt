cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_cmeter LANGUAGES MikroC)
else()
    project(lib_cmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_cmeter STATIC
        src/cmeter.c
        include/cmeter.h
)
add_library(Click.CMeter  ALIAS lib_cmeter)



target_include_directories(lib_cmeter PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_cmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_cmeter PUBLIC MikroSDK.Driver)

