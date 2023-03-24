cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand9 LANGUAGES MikroC)
else()
    project(lib_expand9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand9 STATIC
        src/expand9.c
        include/expand9.h
)
add_library(Click.Expand9  ALIAS lib_expand9)



target_include_directories(lib_expand9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand9 PUBLIC MikroSDK.Driver)
