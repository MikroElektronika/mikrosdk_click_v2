cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless10 LANGUAGES MikroC)
else()
    project(lib_brushless10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless10 STATIC
        src/brushless10.c
        include/brushless10.h
)
add_library(Click.Brushless10  ALIAS lib_brushless10)



target_include_directories(lib_brushless10 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless10 PUBLIC MikroSDK.Driver)

