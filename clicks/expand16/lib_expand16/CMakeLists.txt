cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand16 LANGUAGES MikroC)
else()
    project(lib_expand16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand16 STATIC
        src/expand16.c
        include/expand16.h
)
add_library(Click.Expand16  ALIAS lib_expand16)



target_include_directories(lib_expand16 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand16 PUBLIC MikroSDK.Driver)

