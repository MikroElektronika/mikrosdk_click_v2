cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand6 LANGUAGES MikroC)
else()
    project(lib_expand6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand6 STATIC
        src/expand6.c
        include/expand6.h
)
add_library(Click.Expand6  ALIAS lib_expand6)



target_include_directories(lib_expand6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand6 PUBLIC MikroSDK.Driver)
