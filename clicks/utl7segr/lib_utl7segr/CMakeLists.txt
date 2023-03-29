cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_utl7segr LANGUAGES MikroC)
else()
    project(lib_utl7segr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_utl7segr STATIC
        src/utl7segr.c
        include/utl7segr.h
)
add_library(Click.UT-L7-SEGR  ALIAS lib_utl7segr)



target_include_directories(lib_utl7segr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_utl7segr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_utl7segr PUBLIC MikroSDK.Driver)
