cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current12 LANGUAGES MikroC)
else()
    project(lib_current12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current12 STATIC
        src/current12.c
        include/current12.h
)
add_library(Click.Current12  ALIAS lib_current12)



target_include_directories(lib_current12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current12 PUBLIC MikroSDK.Driver)

