cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand3 LANGUAGES MikroC)
else()
    project(lib_expand3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand3 STATIC
        src/expand3.c
        include/expand3.h
)
add_library(Click.Expand3  ALIAS lib_expand3)



target_include_directories(lib_expand3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand3 PUBLIC MikroSDK.Driver)

