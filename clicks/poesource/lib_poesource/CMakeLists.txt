cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_poesource LANGUAGES MikroC)
else()
    project(lib_poesource LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_poesource STATIC
        src/poesource.c
        include/poesource.h
)
add_library(Click.PoESource  ALIAS lib_poesource)



target_include_directories(lib_poesource PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_poesource PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_poesource PUBLIC MikroSDK.Driver)

