cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand19 LANGUAGES MikroC)
else()
    project(lib_expand19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand19 STATIC
        src/expand19.c
        include/expand19.h
)
add_library(Click.Expand19  ALIAS lib_expand19)



target_include_directories(lib_expand19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand19 PUBLIC MikroSDK.Driver)

