cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog6 LANGUAGES MikroC)
else()
    project(lib_templog6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog6 STATIC
        src/templog6.c
        include/templog6.h
)
add_library(Click.TempLog6  ALIAS lib_templog6)



target_include_directories(lib_templog6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog6 PUBLIC MikroSDK.Driver)
