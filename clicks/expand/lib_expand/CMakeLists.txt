cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand LANGUAGES MikroC)
else()
    project(lib_expand LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand STATIC
        src/expand.c
        include/expand.h
)
add_library(Click.Expand  ALIAS lib_expand)



target_include_directories(lib_expand PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand PUBLIC MikroSDK.Driver)
