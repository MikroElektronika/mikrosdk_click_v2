cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current17 LANGUAGES MikroC)
else()
    project(lib_current17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current17 STATIC
        src/current17.c
        include/current17.h
)
add_library(Click.Current17  ALIAS lib_current17)



target_include_directories(lib_current17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current17 PUBLIC MikroSDK.Driver)

