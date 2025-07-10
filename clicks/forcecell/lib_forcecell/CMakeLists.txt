cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_forcecell LANGUAGES MikroC)
else()
    project(lib_forcecell LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_forcecell STATIC
        src/forcecell.c
        include/forcecell.h
)
add_library(Click.ForceCell  ALIAS lib_forcecell)



target_include_directories(lib_forcecell PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_forcecell PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_forcecell PUBLIC MikroSDK.Driver)

