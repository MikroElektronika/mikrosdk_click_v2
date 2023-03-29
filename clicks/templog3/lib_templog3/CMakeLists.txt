cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog3 LANGUAGES MikroC)
else()
    project(lib_templog3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog3 STATIC
        src/templog3.c
        include/templog3.h
)
add_library(Click.TempLog3  ALIAS lib_templog3)



target_include_directories(lib_templog3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog3 PUBLIC MikroSDK.Driver)
