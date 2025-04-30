cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tds LANGUAGES MikroC)
else()
    project(lib_tds LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tds STATIC
        src/tds.c
        include/tds.h
)
add_library(Click.TDS  ALIAS lib_tds)



target_include_directories(lib_tds PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tds PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tds PUBLIC MikroSDK.Driver)

