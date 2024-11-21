cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current14 LANGUAGES MikroC)
else()
    project(lib_current14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current14 STATIC
        src/current14.c
        include/current14.h
)
add_library(Click.Current14  ALIAS lib_current14)



target_include_directories(lib_current14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current14 PUBLIC MikroSDK.Driver)

