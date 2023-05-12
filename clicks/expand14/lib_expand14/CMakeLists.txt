cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand14 LANGUAGES MikroC)
else()
    project(lib_expand14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand14 STATIC
        src/expand14.c
        include/expand14.h
)
add_library(Click.Expand14  ALIAS lib_expand14)



target_include_directories(lib_expand14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand14 PUBLIC MikroSDK.Driver)
