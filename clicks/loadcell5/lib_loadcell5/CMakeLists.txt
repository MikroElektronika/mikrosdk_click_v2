cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell5 LANGUAGES MikroC)
else()
    project(lib_loadcell5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell5 STATIC
        src/loadcell5.c
        include/loadcell5.h
)
add_library(Click.LoadCell5  ALIAS lib_loadcell5)



target_include_directories(lib_loadcell5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell5 PUBLIC MikroSDK.Driver)
