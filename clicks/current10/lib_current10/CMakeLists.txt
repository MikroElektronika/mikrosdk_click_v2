cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current10 LANGUAGES MikroC)
else()
    project(lib_current10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current10 STATIC
        src/current10.c
        include/current10.h
)
add_library(Click.Current10  ALIAS lib_current10)



target_include_directories(lib_current10 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current10 PUBLIC MikroSDK.Driver)

