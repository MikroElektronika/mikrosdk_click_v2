cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand17 LANGUAGES MikroC)
else()
    project(lib_expand17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand17 STATIC
        src/expand17.c
        include/expand17.h
)
add_library(Click.Expand17  ALIAS lib_expand17)



target_include_directories(lib_expand17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand17 PUBLIC MikroSDK.Driver)

