cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_templog4 LANGUAGES MikroC)
else()
    project(lib_templog4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_templog4 STATIC
        src/templog4.c
        include/templog4.h
)
add_library(Click.TempLog4  ALIAS lib_templog4)



target_include_directories(lib_templog4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_templog4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_templog4 PUBLIC MikroSDK.Driver)
