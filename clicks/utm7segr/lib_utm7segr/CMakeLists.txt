cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_utm7segr LANGUAGES MikroC)
else()
    project(lib_utm7segr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_utm7segr STATIC
        src/utm7segr.c
        include/utm7segr.h
)
add_library(Click.UT-M7-SEGR  ALIAS lib_utm7segr)



target_include_directories(lib_utm7segr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_utm7segr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_utm7segr PUBLIC MikroSDK.Driver)
