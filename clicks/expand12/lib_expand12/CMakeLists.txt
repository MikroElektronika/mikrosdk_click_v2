cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand12 LANGUAGES MikroC)
else()
    project(lib_expand12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand12 STATIC
        src/expand12.c
        include/expand12.h
)
add_library(Click.Expand12  ALIAS lib_expand12)



target_include_directories(lib_expand12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand12 PUBLIC MikroSDK.Driver)
