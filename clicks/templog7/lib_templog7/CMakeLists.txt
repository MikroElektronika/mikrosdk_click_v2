cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog7 LANGUAGES MikroC)
else()
    project(lib_templog7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog7 STATIC
        src/templog7.c
        include/templog7.h
)
add_library(Click.TempLog7  ALIAS lib_templog7)



target_include_directories(lib_templog7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog7 PUBLIC MikroSDK.Driver)

