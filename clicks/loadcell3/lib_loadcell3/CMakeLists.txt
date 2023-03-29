cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell3 LANGUAGES MikroC)
else()
    project(lib_loadcell3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell3 STATIC
        src/loadcell3.c
        include/loadcell3.h
)
add_library(Click.LoadCell3  ALIAS lib_loadcell3)



target_include_directories(lib_loadcell3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell3 PUBLIC MikroSDK.Driver)
