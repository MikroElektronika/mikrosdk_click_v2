cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uts7segr LANGUAGES MikroC)
else()
    project(lib_uts7segr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uts7segr STATIC
        src/uts7segr.c
        include/uts7segr.h
)
add_library(Click.UT-S7-SEGR  ALIAS lib_uts7segr)



target_include_directories(lib_uts7segr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uts7segr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uts7segr PUBLIC MikroSDK.Driver)
