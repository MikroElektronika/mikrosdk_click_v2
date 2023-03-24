cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_loadcell4 LANGUAGES MikroC)
else()
    project(lib_loadcell4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_loadcell4 STATIC
        src/loadcell4.c
        include/loadcell4.h
)
add_library(Click.LoadCell4  ALIAS lib_loadcell4)



target_include_directories(lib_loadcell4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_loadcell4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_loadcell4 PUBLIC MikroSDK.Driver)
