cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_efuse2 LANGUAGES MikroC)
else()
    project(lib_efuse2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_efuse2 STATIC
        src/efuse2.c
        include/efuse2.h
)
add_library(Click.eFuse2  ALIAS lib_efuse2)



target_include_directories(lib_efuse2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_efuse2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_efuse2 PUBLIC MikroSDK.Driver)
