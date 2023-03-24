cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog5 LANGUAGES MikroC)
else()
    project(lib_templog5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog5 STATIC
        src/templog5.c
        include/templog5.h
)
add_library(Click.TempLog5  ALIAS lib_templog5)



target_include_directories(lib_templog5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog5 PUBLIC MikroSDK.Driver)
