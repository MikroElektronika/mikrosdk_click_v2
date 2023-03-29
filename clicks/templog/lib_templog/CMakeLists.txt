cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog LANGUAGES MikroC)
else()
    project(lib_templog LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog STATIC
        src/templog.c
        include/templog.h
)
add_library(Click.TempLog  ALIAS lib_templog)



target_include_directories(lib_templog PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog PUBLIC MikroSDK.Driver)
